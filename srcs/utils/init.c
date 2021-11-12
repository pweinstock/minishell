/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:53:47 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/12 15:52:56 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execute.h"

void	init_data(t_data *data, char **envp)
{
	int envnum;

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
	char **delete = malloc(sizeof(char*) * 5);

	delete[0] = "rm";
	delete[1] = "-f";
	delete[2] = ".temp1";
	delete[3] = ".temp2";
	delete[4] = NULL;
	execute(delete, data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
}
