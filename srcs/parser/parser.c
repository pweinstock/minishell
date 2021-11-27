/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:35:05 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/27 20:26:27 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_lex *lex, t_data *data)
{
	t_lex	*temp;
	t_lex	*line_lst;

	temp = lex;
	line_lst = NULL;
	data->is_piped = FALSE;
	data->is_heredoc = FALSE;
	while (lex)
	{	
		if (lex->type == PIPE)
		{
			if (!lex->next || lex->next->type == PIPE)
				return (1);
			pipex(data, &line_lst);
		}
		else if (!parser2(&lex, data, &line_lst, temp))
			return (1);
		lex = lex->next;
	}
	if (!line_lst && free_list(temp) && close(data->fd_in))
		return (1);
	parser3(data, &line_lst, temp);
	return (1);
}

int	parser2(t_lex **lex, t_data *data, t_lex **line_lst, t_lex *temp)
{
	if ((*lex)->type == OUTPUT)
	{
		if (!output(lex, data, temp))
			return (0);
	}
	else if ((*lex)->type == INPUT)
	{
		if (!input(lex, data, temp))
			return (0);
	}
	else if ((*lex)->type == APPEND)
	{
		if (!append(lex, data, temp))
			return (0);
	}
	else if ((*lex)->type == HEREDOC)
	{
		if (!heredoc(lex, data))
			return (0);
	}
	else if ((*lex)->type == WORD)
		word(lex, line_lst);
	return (1);
}

int	parser3(t_data *data, t_lex **line_lst, t_lex *temp)
{
	execute(str_array(*line_lst), data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->fd_in);
	free_list(temp);
	return (1);
}

int	word(t_lex **lex, t_lex **line_lst)
{
	t_lex	*element;

	if (*line_lst == NULL)
		*line_lst = ft_lexnew((*lex)->str, WORD);
	else
	{
		element = ft_lexnew((*lex)->str, WORD);
		ft_lexadd_back(*line_lst, element);
		*line_lst = element;
	}
	return (1);
}

int	heredoc(t_lex **lex, t_data *data)
{
	char	*heredoc;

	if (!redir_check(lex))
		return (0);
	else
	{
		data->is_heredoc = TRUE;
		if (data->fd_in != STDIN_FILENO)
			close(data->fd_in);
		data->fd_in = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		dup2(data->original_stdout, data->fd_out);
		signal(SIGINT, heredoc_signal);
		while (1)
		{
			heredoc = readline("heredoc> ");
			if (!heredoc)
				return (0);
			if (heredoc[0] != 0 && ft_strlen(heredoc) == ft_strlen((*lex)->str) \
			&& !ft_strncmp((*lex)->str, heredoc, ft_strlen(heredoc)))
				break ;
			write(data->fd_in, heredoc, ft_strlen(heredoc));
			write(data->fd_in, "\n", 1);
		}
	}
	return (1);
}

int	input(t_lex **lex, t_data *data, t_lex *temp)
{
	if (!redir_check(lex))
		return (0);
	else
	{
		data->fd_in = open((*lex)->str, O_RDWR, S_IRWXU);
		if (data->fd_in == -1)
		{
			perror((*lex)->str);
			free_list(temp);
			return (0);
		}
	}
	return (1);
}

int	append(t_lex **lex, t_data *data, t_lex *temp)
{
	if (!redir_check(lex))
		return (0);
	else
	{
		close(data->fd_out);
		data->fd_out = open((*lex)->str, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
		if (data->fd_out == -1)
		{
			perror((*lex)->str);
			free_list(temp);
			return (0);
		}
	}
	data->redirection = 1;
	return (1);
}

int	output(t_lex **lex, t_data *data, t_lex *temp)
{
	if (!redir_check(lex))
		return (0);
	else
	{
		close(data->fd_out);
		data->fd_out = open((*lex)->str, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (data->fd_out == -1)
		{
			perror((*lex)->str);
			free_list(temp);
			return (0);
		}	
	}
	data->redirection = 1;
	return (1);
}

int	pipex(t_data *data, t_lex **line_lst)
{
	data->is_piped = TRUE;
	if (!data->redirection)
	{
		if (!data->file_out)
			data->file_out = ".temp1";
		if (!data->file_in)
			data->file_in = ".temp2";
		data->fd_out = open(data->file_out, 512 | 2 | 1024, S_IRWXU);
	}
	execute(str_array(*line_lst), data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->fd_out);
	close(data->fd_in);
	if (!data->redirection)
	{
		data->file = data->file_in;
		data->file_in = data->file_out;
		data->file_out = data->file;
		data->fd_in = open(data->file_in, O_CREAT | O_RDWR, S_IRWXU);
	}
	data->fd_out = STDOUT_FILENO;
	data->redirection = 0;
	*line_lst = NULL;
	return (1);
}

char	**str_array(t_lex *lst)
{
	char	**line;
	int		i;
	t_lex	*temp;

	while (lst->previous != NULL)
		lst = lst->previous;
	temp = lst;
	line = ft_calloc(lex_len(lst) + 1, sizeof(char **));
	lst = temp;
	i = 0;
	while (lst)
	{
		line[i] = lst->str;
		i++;
		lst = lst->next;
	}
	line[i] = NULL;
	free_list(temp);
	return (line);
}

int	redir_check(t_lex **lex)
{
	*lex = (*lex)->next;
	if (!*lex)
	{
		redir_err(NEWL);
		return (0);
	}
	else if ((*lex)->type != WORD)
	{
		redir_err((*lex)->type);
		return (0);
	}
	return (1);
}

void	redir_err(int type)
{
	write(STDOUT_FILENO, "minishell: syntax error near unexpected token ", 46);
	if (type == OUTPUT)
		write(STDOUT_FILENO, "`>'\n", 4);
	else if (type == APPEND)
		write(STDOUT_FILENO, "`>>'\n", 5);
	else if (type == INPUT)
		write(STDOUT_FILENO, "`>'\n", 4);
	else if (type == HEREDOC)
		write(STDOUT_FILENO, "`<<'\n", 5);
	else if (type == PIPE)
		write(STDOUT_FILENO, "`|'\n", 4);
	else if (type == NEWL)
		write(STDOUT_FILENO, "`newline'\n", 10);
	return ;
}
