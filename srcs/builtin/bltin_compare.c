/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:40:28 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/02 15:43:37 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	str_compare(const char *str1, char *str2)
{
	int index;

	if (str1 == NULL || str2 == NULL)
		return (0);
	index = 0;
	while (str1[index] != '\0' || str2[index] != '\0')
	{
		if (str1[index] != str2[index])
			return (0);
		index++;
	}
	if (str1[index] != str2[index])
		return (0);
	return (1);
}

int	bltin_compare(char *needle)
{
	int	index;

	index = 0;
	while (g_bltin_cmds[index] != NULL)
	{
		if (str_compare(g_bltin_cmds[index], needle) != 0)
			return (index);
		index++;
	}
	return (-1);
}
