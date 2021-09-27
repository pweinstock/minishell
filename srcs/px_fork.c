/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:16:08 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 15:17:06 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_process(t_data *data, char **envp)
{
	dup2(data->fd_temp, STDIN_FILENO);
	close(data->end[0]);
	if (data->cmd_count + 1 < data->cmd_amt)
		dup2(data->end[1], STDOUT_FILENO);
	else
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
		close(data->end[1]);
	}
	runcmd(data, data->cmd[data->cmd_count], envp);
	return ;
}

int	forking(t_data *data, char **envp)
{
	data->cmd_count = 0;
	dup2(data->fd_in, data->fd_temp);
	while (data->cmd[data->cmd_count] != NULL)
	{
		if (pipe(data->end) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		data->child = fork();
		if (data->child == -1)
			exit(EXIT_FAILURE);
		if (data->child == 0)
			child_process(data, envp);
		while (wait(NULL) != -1 || errno != ECHILD)
			continue ;
		close(data->end[1]);
		dup2(data->end[0], data->fd_temp);
		close(data->end[0]);
		data->cmd_count++;
	}
	return (0);
}
