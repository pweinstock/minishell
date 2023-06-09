/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:35:05 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/03 11:51:15 by pweinsto         ###   ########.fr       */
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
			if ((!lex->next || lex->next->type == PIPE) && free_list(temp))
				return (free_list(line_lst));
			pipex(data, &line_lst);
			data->is_heredoc = FALSE;
		}
		else if (!parser2(&lex, data, &line_lst) && free_list(temp))
			return (free_list(line_lst));
		lex = lex->next;
	}
	if (!line_lst && free_list(temp))
		return (1);
	parser3(data, &line_lst, temp);
	return (1);
}

int	parser2(t_lex **lex, t_data *data, t_lex **line_lst)
{
	if ((*lex)->type == OUTPUT)
	{
		if (!output(lex, data))
			return (0);
	}
	else if ((*lex)->type == INPUT)
	{
		if (!input(lex, data))
			return (0);
	}
	else if ((*lex)->type == APPEND)
	{
		if (!append(lex, data))
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
