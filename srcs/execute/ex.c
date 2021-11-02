/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:39:39 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"

int	execute(char **input, t_data *data)
{
	t_pipex	p_strct;

	ft_bzero(&p_strct, sizeof(t_pipex));
	// if (error_handler(&p_strct, input) == ERROR)
	// 	return (1);
	write(2, input[0], ft_strlen(input[0]));
	write(2, input[1], ft_strlen(input[1]));
	p_strct.cmd = input;
	p_strct.envp = data->envp;
	p_strct.fd_in = data->fd_in;
	p_strct.fd_out = data->fd_out;
	parsing_envpath(&p_strct, p_strct.envp);
	if (forking(&p_strct, p_strct.envp) == ERROR)
		return (1);
	free(p_strct.envpath);
	p_strct.envpath = NULL;
	free(p_strct.cmd);
	p_strct.cmd = NULL;
	return (0);
}
