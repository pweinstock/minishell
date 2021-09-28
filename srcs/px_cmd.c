/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:33:30 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/28 08:52:09 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_run_err(t_pipex *p_strct, int index, char **cmd, char *cmd_prefix)
{
	if (p_strct->envpath == NULL)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free(cmd_prefix);
		exit(EXIT_FAILURE);
	}
	if (p_strct->envpath[index] == NULL)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free(cmd_prefix);
		exit(EXIT_FAILURE);
	}
}

void	runcmd(t_pipex *p_strct, char **cmd, char **envp)
{
	char	*temp;
	char	*cmd_prefix;
	char	*full_cmdpath;
	int		index;

	index = 0;
	cmd_prefix = ft_strdup(cmd[0]);
	// write(2, cmd_prefix, ft_strlen(cmd_prefix));
	ft_run_err(p_strct, index, cmd, cmd_prefix);
	while (p_strct->envpath[index] != NULL)
	{
		temp = ft_strjoin(p_strct->envpath[index], "/");
		// write(2, p_strct->envpath[index], ft_strlen(p_strct->envpath[index]));
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
		ft_run_err(p_strct, index, cmd, cmd_prefix);
	}
}
