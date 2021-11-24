/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:35:05 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/24 19:00:01 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_lex *lex, t_data *data)
{
	t_lex	*temp;
	t_lex	*line_lst;
	t_lex	*element;
	char	**array;
	char	*heredoc;

	temp = lex;
	line_lst = NULL;
	data->is_piped = FALSE;
	data->is_heredoc = FALSE;
	while (lex)
	{
		if (lex->type == PIPE)
		{
			data->is_piped = TRUE;
			if (!data->redirection)
			{
				if (!data->file_out)
					data->file_out = ".temp1";
				if (!data->file_in)
					data->file_in = ".temp2";
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
			close(data->fd_out);
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
			{
				if ((data->fd_out = open(lex->str, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU)) == -1)
				{
					perror(lex->str);
					free_list(temp);
					return (1);
				}
			}
			data->redirection = 1;
		}
		else if (lex->type == INPUT)
		{
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
			{
				if ((data->fd_in = open(lex->str, O_RDWR, S_IRWXU)) == -1)
					perror(lex->str);
					free_list(temp);
					return (1);
			}
			//write(data->original_stdout, (*lex)->str, ft_strlen((*lex)->str));
		}
		else if (lex->type == APPEND)
		{
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
			{
				if ((data->fd_out = open(lex->str, O_CREAT|O_RDWR|O_APPEND, S_IRWXU)) == -1)
				{
					perror(lex->str);
					free_list(temp);
					return (1);
				}
			}
		}
		else if (lex->type == HEREDOC)
		{
			// printf("lextype: %i\n", lex->type);
			lex = lex->next;
			if (lex->type != WORD)
				printf("error\n");
			else
			{
				data->is_heredoc = TRUE;
				if (data->fd_in != STDIN_FILENO)
					close(data->fd_in);
				data->fd_in = open(".heredoc", O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
				printf("|%i|\n", data->fd_in);
				dup2(data->original_stdout, data->fd_out);
				while (1)
				{
					heredoc = readline("heredoc> ");
					if (!heredoc)
						break;
					if (heredoc[0] != '\0' && ft_strlen(heredoc) == ft_strlen(lex->str) && !ft_strncmp(lex->str, heredoc, ft_strlen(heredoc)))
						break;
					signal(SIGINT, heredoc_signal);
					if (heredoc_break == TRUE)
					{
						heredoc_break = FALSE;
						break;
					}
					write(data->fd_in, heredoc, ft_strlen(heredoc));
					write(data->fd_in, "\n", 1);
				}
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
	// print_lex(line_lst);
	if (!line_lst)
	{
		write(data->original_stdout, "Error\n", 6);
		return (0);
	}
	array = str_array(line_lst);
	// dup2(data->fd_in, STDIN_FILENO);
	// dup2(data->fd_out, STDOUT_FILENO);
	// if (array[0] != NULL)
	// 	printf("array: %s\n", array[0]);
		//write(data->original_stdout, array[0], ft_strlen(array[0]));
	write(data->original_stdout, "\n", 1);
	execute(array, data);
	// printf("Test\n");
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
	// while (*line)
	// {
	// 	printf("%s\n", *line);
	// 	line++;
	// }
	return (line);
}

