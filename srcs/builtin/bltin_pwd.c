/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 08:51:04 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/27 12:36:23 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	bltin_pwd(t_pipex *p_strct, char **cmd)
{
	char *cwd;

	if (cmd[1])
	{
		write(2, "pwd: Too many options.\n", 24);
		return ;
	}
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, p_strct->data->fd_out);
	ft_putchar_fd('\n', p_strct->data->fd_out);
	free(cwd);
	return ;
}
