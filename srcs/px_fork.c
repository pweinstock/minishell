/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:16:08 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/28 08:51:02 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(t_pipex *p_strct, t_data *data, char **envp)
{
	dup2(p_strct->fd_temp, STDIN_FILENO);
	close(p_strct->end[0]);
	if (p_strct->cmd_count + 1 < p_strct->cmd_amt)
		dup2(p_strct->end[1], STDOUT_FILENO);
	else
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
		close(p_strct->end[1]);
	}
	runcmd(p_strct, p_strct->cmd[p_strct->cmd_count], envp);
	return ;
}

int	forking(t_pipex *p_strct, t_data *data, char **envp)
{
	p_strct->cmd_count = 0;
	dup2(data->fd_in, p_strct->fd_temp);
	while (p_strct->cmd[p_strct->cmd_count] != NULL)
	{
		if (pipe(p_strct->end) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		p_strct->child = fork();
		if (p_strct->child == -1)
			exit(EXIT_FAILURE);
		if (p_strct->child == 0)
			child_process(p_strct, data, envp);
		while (wait(NULL) != -1 || errno != ECHILD)
			continue ;
		close(p_strct->end[1]);
		dup2(p_strct->end[0], p_strct->fd_temp);
		close(p_strct->end[0]);
		p_strct->cmd_count++;
	}
	return (0);
}
