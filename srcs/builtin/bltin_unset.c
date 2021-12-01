/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:29:43 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/01 09:08:08 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	bltin_unset(t_pipex *p_strct, char **cmd)
{
	int	index;
	int	envnum;

	index = 1;
	while (cmd[index] != NULL)
	{
		envnum = get_envnum(p_strct->data->envp, cmd[index]);
		if (envnum != -1)
			rotate_env(p_strct->data, envnum);
		index++;
	}
	return ;
}
