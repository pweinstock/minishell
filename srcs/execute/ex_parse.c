/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:34:45 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:05:41 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	parsing_envpath(t_pipex *p_strct, char **envp)
{
	int		envnum;
	char *temp;

	envnum = get_envnum(envp, "PATH");
	if (envnum == -1)
	{
		p_strct->envpath = NULL;
		return ;
	}
	temp = envp[envnum];
	temp += 5;
	p_strct->envpath = ft_split(temp, ':');
}
