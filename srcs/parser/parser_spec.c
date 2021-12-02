/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:24:11 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/02 15:51:17 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	word(t_lex **lex, t_lex **line_lst)
{
	t_lex	*element;

	if (*line_lst == NULL)
		*line_lst = ft_lexnew(ft_strdup((*lex)->str), WORD);
	else
	{
		element = ft_lexnew(ft_strdup((*lex)->str), WORD);
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
			free(heredoc);
		}
		free(heredoc);
	}
	return (1);
}

int	input(t_lex **lex, t_data *data)
{
	if (!redir_check(lex))
		return (0);
	else
	{
		data->fd_in = open((*lex)->str, O_RDWR, S_IRWXU);
		if (data->fd_in == -1)
		{
			perror((*lex)->str);
			return (0);
		}
	}
	return (1);
}

int	append(t_lex **lex, t_data *data)
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
			return (0);
		}
	}
	data->redirection = 1;
	return (1);
}

int	output(t_lex **lex, t_data *data)
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
			return (0);
		}
	}
	data->redirection = 1;
	return (1);
}
