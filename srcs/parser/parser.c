/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:35:05 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/10 17:49:10 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_lex *lex, t_data *data)
{
	t_lex	*temp;
	t_lex	*line_lst;
	t_lex	*element;
	char	**array;

	temp = lex;
	line_lst = NULL;
	while (lex)
	{
		if (lex->type == PIPE)
		{
			if (!data->redirection)
			{
				if (!data->file_out)
					data->file_out = "temp1";
				if (!data->file_in)
					data->file_in = "temp2";
				data->fd_out = open(data->file_out, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
			}
			execute(str_array(line_lst), data);
			dup2(data->original_stdin, STDIN_FILENO);
			dup2(data->original_stdout, STDOUT_FILENO);
			close(data->fd_out);
			close(data->fd_in);
			if (!data->redirection)
			{
				data->file = data->file_in;
				data->file_in = data->file_out;
				data->file_out = data->file;
				data->fd_in = open(data->file_in, O_CREAT|O_RDWR, S_IRWXU);
			}
			data->fd_out = STDOUT_FILENO;
			data->redirection = 0;
			line_lst = NULL;
		}
		else if (lex->type == OUTPUT)
		{
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
					data->fd_out = open(lex->str, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
			data->redirection = 1;
		}
		else if (lex->type == INPUT)
		{
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
					data->fd_in = open(lex->str, O_RDONLY, S_IRWXU);
			//write(data->original_stdout, (*lex)->str, ft_strlen((*lex)->str));
		}
		else if (lex->type == APPEND)
		{
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
					data->fd_out = open(lex->str, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
		}
		else if (lex->type == HEREDOC)
		{
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
			{
				//close(data->fd_in);
				if (data->fd_in == STDIN_FILENO)
					data->file_in = "temp2";
				data->fd_in = open(data->file_in, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
				while (1)
				{
					char	*heredoc = readline("heredoc> ");
					if (!ft_strncmp(lex->str, heredoc, ft_strlen(heredoc)) && heredoc[0] != 0)
						break;
					write(data->fd_in, heredoc, ft_strlen(heredoc));
					write(data->fd_in, " | ", 3);
				}
			}
		}
		else if (lex->type == DQUOTE)
		{
			lex = lex->next;
			if (!lex)
				break;
			if (line_lst == NULL && lex->type == WORD)
					line_lst = ft_lexnew(lex->str, WORD);
			else if (lex->type == WORD)
			{
				element = ft_lexnew(lex->str, WORD);
				ft_lexadd_back(line_lst, element);
				line_lst = element;
			}
		}
		else if (lex->type == SQUOTE)
		{
			lex = lex->next;
			if (!lex)
				break;
			if (line_lst == NULL && lex->type == WORD)
					line_lst = ft_lexnew(lex->str, WORD);
			else if (lex->type == WORD)
			{
				element = ft_lexnew(lex->str, WORD);
				ft_lexadd_back(line_lst, element);
				line_lst = element;
			}
		}
		else if (lex->type == CDQUOTE)
		{
			while (lex->type == CDQUOTE)
				lex = lex->next;
			if (lex->type != DQUOTE && lex->type != CDQUOTE)
			{

				if (line_lst == NULL)
					line_lst = ft_lexnew(lex->str, WORD);
				else
					line_lst->str = ft_strjoin(line_lst->str, lex->str);
			}
		}
		else if (lex->type == CSQUOTE)
		{
			while (lex->type == CSQUOTE)
				lex = lex->next;
			if (lex->type != SQUOTE && lex->type != CSQUOTE)
			{

				if (line_lst == NULL)
					line_lst = ft_lexnew(lex->str, WORD);
				else
					line_lst->str = ft_strjoin(line_lst->str, lex->str);
			}
		}
		else if (lex->type == WORD)
		{
			if (line_lst == NULL)
				line_lst = ft_lexnew(lex->str, WORD);
			else
			{
				element = ft_lexnew(lex->str, WORD);
				ft_lexadd_back(line_lst, element);
				line_lst = element;
			}
		}
		lex = lex->next;
	}
	// while (line_lst->previous != NULL)
	// 	line_lst = line_lst->previous;
	//printf("--------------line_lst---------------\n");
	//print_lex(line_lst);
	if (!line_lst)
	{
		write(data->original_stdout, "Error\n", 6);
		return (0);
	}
	array = str_array(line_lst);
	// dup2(data->fd_in, STDIN_FILENO);
	// dup2(data->fd_out, STDOUT_FILENO);
	execute(array, data);
	// close(data->fd_in);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	// if (data->file_in)
	// 	close(data->fd_in);
	// close(data->fd_out);
	close(data->fd_in);
	free_list(temp);
	return (1);
}

char **str_array(t_lex *lst)
{
	char **line;
	int	i;
	t_lex *temp;

	while (lst->previous != NULL)
		lst = lst->previous;
	temp = lst;
	line = malloc(sizeof(char **) * (lex_len(lst) + 1));

	line[lex_len(lst) + 1] = NULL;
	i = 0;
	while (lst)
	{
		line[i] = lst->str;
		i++;
		lst = lst->next;
	}
	free_list(temp);
	// while (*line)
	// {
	// 	printf("%s\n", *line);
	// 	line++;
	// }
	return (line);
}

