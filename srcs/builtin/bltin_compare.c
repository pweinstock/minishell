/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_compare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:40:28 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/01 09:47:15 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bltin_compare(t_data *data, char *needle)
{
	int index;

	index = 0;
	while (data->bltin_cmds[index] != NULL)
	{
		if (ft_strnstr(data->bltin_cmds[index], needle, ft_strlen(needle)) != 0)
			return (index);
		index++;
	}
	return (-1);
}
