/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:20:58 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/11 10:26:23 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bltin_env(t_data *data, char **cmd)
{
	int index;

	if (cmd[1])
	{
		write(2, "env: Too many options.\n", 24);
		return ;
	}
	index = 0;
	while (data->envp[index] != NULL)
	{
		write(1, data->envp[index], ft_strlen(data->envp[index]));
		write(1, "\n", 1);
		index++;
	}
	return ;
}