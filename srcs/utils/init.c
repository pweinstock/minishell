/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:53:47 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/27 18:10:39 by pweinsto         ###   ########.fr       */
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
	data->envp = ft_strarr_copy(envp);
	envnum = get_envnum(data->envp, "OLDPWD");
	if (envnum != -1)
		rotate_env(data, envnum);
}

void	reset(t_data *data)
{
	// ft_bzero(data->str, ft_strlen(data->str));
	// free(data->str);
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_attr);
	data->file_in = NULL;
	data->file_out = NULL;
	data->file = NULL;
	unlink(".heredoc");
	unlink(".temp1");
	unlink(".temp2");
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	return ;
}
