/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:16:08 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/25 09:48:27 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	child_process(t_pipex *p_strct)
{
	if (p_strct->data->is_heredoc == TRUE)
	{
		p_strct->data->fd_in = open(".heredoc", O_RDWR);
		p_strct->data->is_heredoc = FALSE;
	}
	if (dup2(p_strct->data->fd_in, STDIN_FILENO) == -1)
		exit(errno);
	if (dup2(p_strct->data->fd_out, STDOUT_FILENO) == -1)
		exit(errno);
	runcmd(p_strct, p_strct->cmd);
	exit(EXIT_SUCCESS);
}

static void create_child(t_pipex *p_strct)
{
		p_strct->child = fork();
		if (p_strct->child == -1)
			exit(EXIT_FAILURE);
		if (p_strct->child == 0)
			child_process(p_strct);
		waitpid(p_strct->child, &p_strct->data->error_ret, 0);
		p_strct->data->is_child = TRUE;
}

int	forking(t_pipex *p_strct)
{
	int is_bltin;

	is_bltin = 0;
	is_bltin = bltin_compare(p_strct->cmd[0]);
	dup2(p_strct->data->fd_in, STDIN_FILENO);
	dup2(p_strct->data->fd_out, STDOUT_FILENO);
	if (is_bltin != -1 && p_strct->data->is_piped == FALSE)
		p_strct->data->error_ret = runbltin(p_strct, p_strct->cmd, is_bltin);
	else
	{
		if (pipe(p_strct->end) == -1)
		{
			perror("Error");
			return (ERROR);
		}
		create_child(p_strct);
		close(p_strct->end[0]);
		close(p_strct->end[1]);
	}
	// printf("errno %i | %i\n", WEXITSTATUS(p_strct->data->error_ret), p_strct->data->error_ret);
	return (0);
}
