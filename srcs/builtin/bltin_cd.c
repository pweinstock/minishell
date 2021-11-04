/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:39:20 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 10:59:51 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	bltin_cd(t_pipex *p_strct, char **cmd)
{
	char *cwd;

	if (chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	cwd = getcwd(NULL, 0);
	cwd += ft_revchrsrch(cwd, '/') + 1;
	free(p_strct->data->path_prefix);
	p_strct->data->path_prefix = ft_strdup(cwd);
	return ;
}
