/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:53:47 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/17 14:16:50 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	init_data(t_data *data, char **envp)
{
	int	envnum;

	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
	data->path_prefix = ft_strdup("minishell");
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->envp = envp;
	envnum = get_envnum(data->envp, "OLDPWD");
	if (envnum != -1)
		rotate_env(data, envnum);
}

void	rm(t_data *data)
{
	char	*temp[6];

	temp[0] = "/bin/rm";
	temp[1] = "-f";
	temp[2] = ".heredoc";
	temp[3] = ".temp1";
	temp[4] = ".temp2";
	temp[5] = NULL;
	execute(temp, data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
}
