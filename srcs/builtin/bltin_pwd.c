/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 08:51:04 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/01 09:08:01 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	bltin_pwd(t_pipex *p_strct, char **cmd)
{
	char	*cwd;

	if (cmd[1])
	{
		ft_putstr_fd("minishell: pwd: Too many options.\n", 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, p_strct->data->fd_out);
	ft_putchar_fd('\n', p_strct->data->fd_out);
	free(cwd);
	return (0);
}
