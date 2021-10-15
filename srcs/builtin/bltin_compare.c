/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:40:28 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/14 13:23:22 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bltin_compare(char *needle)
{
	int index;

	index = 0;
	while (g_bltin_cmds[index] != NULL)
	{
		if (ft_strnstr(g_bltin_cmds[index], needle, ft_strlen(needle)) != 0)
			return (index);
		index++;
	}
	return (-1);
}
