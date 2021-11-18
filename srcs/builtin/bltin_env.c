/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:20:58 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/18 10:19:44 by khirsig          ###   ########.fr       */
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
			write(1, p_strct->data->envp[index], ft_strlen(p_strct->data->envp[index]));
			write(1, "\n", 1);
		}
		index++;
	}
	return ;
}