/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:20:58 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/26 19:51:00 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	bltin_env(t_pipex *p_strct, char **cmd)
{
	int index;

	if (cmd[1])
	{
		write(2, "env: Too many options.\n", 24);
		return ;
	}
	index = 0;
	while (p_strct->data->envp[index] != NULL)
	{
		if (ft_chrsrch(p_strct->data->envp[index], '=') != -1)
		{
			ft_putstr_fd(p_strct->data->envp[index], p_strct->data->fd_out);
			ft_putstr_fd("\n", p_strct->data->fd_out);
		}
		index++;
	}
	return ;
}