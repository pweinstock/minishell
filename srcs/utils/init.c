/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:53:47 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/02 15:10:32 by khirsig          ###   ########.fr       */
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
	data->file_in = NULL;
	data->file_out = NULL;
	data->envp = ft_strarr_copy(envp);
	envnum = get_envnum(data->envp, "OLDPWD");
	if (envnum != -1)
		rotate_env(data, envnum);
}

void	reset(t_data *data)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &data->original_attr);
	data->file_in = NULL;
	data->file_out = NULL;
	data->file = NULL;
	unlink(".heredoc");
	unlink(".temp1");
	unlink(".temp2");
	data->is_piped = 0;
	data->is_heredoc = 0;
	data->redirection = 0;
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	return ;
}
