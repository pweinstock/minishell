/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:35:05 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/02 16:36:10 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser(t_lex **lex, t_data *data)
{
	//char	**line;
	t_lex	*line_lst;
	t_lex	*element;

	line_lst = NULL;
	while (*lex)
	{
		if ((*lex)->type == PIPE)
		{
			data->fd_out = open("temp", O_CREAT|O_RDWR, S_IRWXU);
			dup2(data->fd_in, STDIN_FILENO);
			dup2(data->fd_out, STDOUT_FILENO);
			execute(str_array(line_lst), data);
			data->fd_in = data->fd_out;
			dup2(data->original_stdin, STDIN_FILENO);
			dup2(data->original_stdout, STDOUT_FILENO);
			line_lst = NULL;
		}
		else if ((*lex)->type == OUTPUT)
		{
			*lex = (*lex)->next;
			if ((*lex)->type != WORD)
				printf("error\n");
			else
					data->fd_out = open((*lex)->str, O_CREAT|O_WRONLY, S_IRWXU);
		}
		else if ((*lex)->type == INPUT)
		{
			*lex = (*lex)->next;
			if ((*lex)->type != WORD)
				printf("error\n");
			else
					data->fd_in = open((*lex)->str, O_RDONLY, S_IRWXU);
		}
		else if ((*lex)->type == APPEND)
		{
			*lex = (*lex)->next;
			if ((*lex)->type != WORD)
				printf("error\n");
			else
					data->fd_out = open((*lex)->str, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
		}
		else if ((*lex)->type == HEREDOC)
		{
			*lex = (*lex)->next;
			if ((*lex)->type != WORD)
				printf("error\n");
			else
			{
				while (1)
				{
					char	*heredoc = readline("heredoc> ");
					if (!ft_strncmp((*lex)->str, heredoc, ft_strlen(heredoc)) && heredoc[0] != 0)
						break;
					write(data->fd_in, heredoc, ft_strlen(heredoc));
					write(data->fd_in, "\n", 1);
				}
			}
		}
		else if ((*lex)->type == DQUOTE)
		{
			*lex = (*lex)->next;
			if (!*lex)
				break;
			if (line_lst == NULL && (*lex)->type == WORD)
					line_lst = ft_lexnew((*lex)->str, WORD);
			else if ((*lex)->type == WORD)
			{
				element = ft_lexnew((*lex)->str, WORD);
				ft_lexadd_back(line_lst, element);
				line_lst = element;
			}
		}
		else if ((*lex)->type == SQUOTE)
		{
			*lex = (*lex)->next;
			if (!*lex)
				break;
			if (line_lst == NULL && (*lex)->type == WORD)
					line_lst = ft_lexnew((*lex)->str, WORD);
			else if ((*lex)->type == WORD)
			{
				element = ft_lexnew((*lex)->str, WORD);
				ft_lexadd_back(line_lst, element);
				line_lst = element;
			}
		}
		else if ((*lex)->type == CDQUOTE)
		{
			while ((*lex)->type == CDQUOTE)
				*lex = (*lex)->next;
			if ((*lex)->type != DQUOTE && (*lex)->type != CDQUOTE)
			{

				if (line_lst == NULL)
					line_lst = ft_lexnew((*lex)->str, WORD);
				else
					line_lst->str = ft_strjoin(line_lst->str, (*lex)->str);
			}
		}
		else if ((*lex)->type == CSQUOTE)
		{
			while ((*lex)->type == CSQUOTE)
				*lex = (*lex)->next;
			if ((*lex)->type != SQUOTE && (*lex)->type != CSQUOTE)
			{

				if (line_lst == NULL)
					line_lst = ft_lexnew((*lex)->str, WORD);
				else
					line_lst->str = ft_strjoin(line_lst->str, (*lex)->str);
			}
		}
		else if ((*lex)->type == WORD)
		{
			if (line_lst == NULL)
				line_lst = ft_lexnew((*lex)->str, WORD);
			else
			{
				element = ft_lexnew((*lex)->str, WORD);
				ft_lexadd_back(line_lst, element);
				line_lst = element;
			}
		}
		*lex = (*lex)->next;
	}
	// while (line_lst->previous != NULL)
	// 	line_lst = line_lst->previous;
	//printf("--------------line_lst---------------\n");
	//print_lex(line_lst);
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	execute(str_array(line_lst), data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	return (1);
}

char **str_array(t_lex *lst)
{
	char **line;
	int	i;

	while (lst->previous != NULL)
		lst = lst->previous;
	line = malloc(sizeof(char **) * (lex_len(lst) + 1));

	line[lex_len(lst) + 1] = NULL;
	i = 0;
	while (lst)
	{
		line[i] = lst->str;
		i++;
		lst = lst->next;
	}
	// while (*line)
	// {
	// 	printf("%s\n", *line);
	// 	line++;
	// }
	return (line);
}

