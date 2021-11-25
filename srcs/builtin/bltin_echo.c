/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:03:38 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/25 09:50:02 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	echo_write(char *str)
{
	int index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] != '\\' && str[index - 1] != '\\')
			write(1, &str[index], 1);
		index++;
	}
	return ;
}

void	bltin_echo(t_pipex *p_strct, char **cmd)
{
	int	index;
	int	flag;

	(void)p_strct;
	flag = FALSE;
	index = 1;
	if (ft_strnstr(cmd[1], "-n", 2) != 0)
	{
		flag = TRUE;
		index = 2;
	}
	while (cmd[index] != NULL)
	{
		echo_write(cmd[index]);
		if (cmd[index + 1] != NULL)
			write(1, " ", 1);
		index++;
	}
	if (flag == TRUE )
		return ;
	write(1, "\n", 1);
	return ;
}
