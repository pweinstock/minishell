/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:29:43 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 11:01:59 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	rotate_env(t_pipex *p_strct, int envnum)
{
	while (p_strct->data->envp[envnum] != NULL)
	{
		if (p_strct->data->envp[envnum + 1] != NULL)
			p_strct->data->envp[envnum] = ft_strdup(p_strct->data->envp[envnum + 1]);
		else
			p_strct->data->envp[envnum] = NULL;
		envnum++;
	}
	return ;
}

void	bltin_unset(t_pipex *p_strct, char **cmd)
{
	int index;
	int	envnum;

	index = 1;
	while (cmd[index] != NULL)
	{
		envnum = get_envnum(p_strct->data->envp, cmd[index]);
		if (envnum != -1)
			rotate_env(p_strct, envnum);
		index++;
	}
	return ;
}
