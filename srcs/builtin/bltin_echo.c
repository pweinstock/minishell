/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:03:38 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/01 13:13:23 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	echo_write(char *str, int fd)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		ft_putchar_fd(str[index], fd);
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
	while (ft_strnstr(cmd[index], "-n", 2) != 0 && cmd[index][2] == '\0')
	{
		flag = TRUE;
		index++;
	}
	while (cmd[index] != NULL)
	{
		echo_write(cmd[index], p_strct->data->fd_out);
		if (cmd[index + 1] != NULL)
			ft_putchar_fd(' ', p_strct->data->fd_out);
		index++;
	}
	if (flag == TRUE)
		return ;
	ft_putchar_fd('\n', p_strct->data->fd_out);
	return ;
}
