/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:16:08 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 10:58:02 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	child_process(t_pipex *p_strct)
{
	dup2(p_strct->data->fd_in, STDIN_FILENO);
	dup2(p_strct->data->fd_out, STDOUT_FILENO);
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
		while (wait(NULL) != -1 || errno != ECHILD)
			continue ;
}

int	forking(t_pipex *p_strct)
{
	int is_bltin;

	is_bltin = 0;
	is_bltin = bltin_compare(p_strct->cmd[0]);
	if (is_bltin != -1)
		runbltin(p_strct, p_strct->cmd, is_bltin);
	else
		create_child(p_strct);
	return (0);
}
