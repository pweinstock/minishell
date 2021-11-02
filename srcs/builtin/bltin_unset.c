/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:29:43 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:22:35 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	rotate_env(t_pipex *p_strct, int envnum)
{
	while (p_strct->envp[envnum] != NULL)
	{
		if (p_strct->envp[envnum + 1] != NULL)
			p_strct->envp[envnum] = ft_strdup(p_strct->envp[envnum + 1]);
		else
			p_strct->envp[envnum] = NULL;
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
		envnum = get_envnum(p_strct->envp, cmd[index]);
		if (envnum != -1)
			rotate_env(p_strct, envnum);
		index++;
	}
	return ;
}
