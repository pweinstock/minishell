/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:29:43 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/11 11:17:04 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	rotate_env(t_data *data, int envnum)
{
	while (data->envp[envnum] != NULL)
	{
		if (data->envp[envnum + 1] != NULL)
			data->envp[envnum] = ft_strdup(data->envp[envnum + 1]);
		else
			data->envp[envnum] = NULL;
		envnum++;
	}
	return ;
}

void	bltin_unset(t_data *data, char **cmd)
{
	int index;
	int	envnum;

	index = 1;
	while (cmd[index] != NULL)
	{
		envnum = get_envnum(data, cmd[index]);
		if (envnum != -1)
			rotate_env(data, envnum);
		index++;
	}
	return ;
}
