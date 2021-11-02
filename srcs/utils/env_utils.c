/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:54:54 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:05:29 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	get_envnum(char **envp, char *needle)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], needle, ft_strlen(envp[i])) != 0)
			return (i);
		i++;
	}
	return (-1);
}
