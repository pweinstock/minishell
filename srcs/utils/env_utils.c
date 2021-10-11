/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:54:54 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/11 10:55:41 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_envnum(t_data *data, char *needle)
{
	int i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strnstr(data->envp[i], needle, ft_strlen(data->envp[i])) != 0)
			return (i);
		i++;
	}
	return (-1);
}
