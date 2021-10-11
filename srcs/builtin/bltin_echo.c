/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:03:38 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/11 10:13:38 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_write(char *str)
{
	int index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] != '\\' && str[index - 1] != '\\')
			write(1, &str[index], 1);
		index++;
	}
	write(1, " ", 1);
	return ;
}

void	bltin_echo(char **cmd)
{
	int	index;

	index = 1;
	while (cmd[index] != NULL)
	{
		echo_write(cmd[index]);
		index++;
	}
	write(1, "\n", 2);
	return ;
}
