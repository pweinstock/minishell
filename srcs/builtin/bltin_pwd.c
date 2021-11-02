/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 08:51:04 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:11:07 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	bltin_pwd(char **cmd)
{
	char *cwd;

	if (cmd[1])
	{
		write(2, "pwd: Too many options.\n", 24);
		return ;
	}
	cwd = getcwd(NULL, 0);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 2);
	free(cwd);
	return ;
}
