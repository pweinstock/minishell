/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:33:30 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 17:04:31 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_run_err(t_data *data, int index, char **cmd, char *cmd_prefix)
{
	if (data->envpath == NULL)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free(cmd_prefix);
		exit(EXIT_FAILURE);
	}
	if (data->envpath[index] == NULL)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free(cmd_prefix);
		exit(EXIT_FAILURE);
	}
}

void	runcmd(t_data *data, char **cmd, char **envp)
{
	char	*temp;
	char	*cmd_prefix;
	char	*full_cmdpath;
	int		index;

	index = 0;
	cmd_prefix = ft_strdup(cmd[0]);
	ft_run_err(data, index, cmd, cmd_prefix);
	while (data->envpath[index] != NULL)
	{
		temp = ft_strjoin(data->envpath[index], "/");
		// write(2, data->envpath[index], ft_strlen(data->envpath[index]));
		full_cmdpath = ft_strjoin(temp, cmd_prefix);
		// write(2, full_cmdpath, ft_strlen(full_cmdpath));
		// write(2, "\n", 2);
		if (access(full_cmdpath, F_OK) != -1)
		{
			execve(full_cmdpath, cmd, envp);
			free(cmd_prefix);
			return ;
		}
		free(temp);
		free(full_cmdpath);
		index++;
		ft_run_err(data, index, cmd, cmd_prefix);
	}
}
