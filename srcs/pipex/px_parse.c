/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:34:45 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/11 10:59:33 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_envpath(t_data *data, t_pipex *p_strct, char **envp)
{
	int		envnum;
	char *temp;

	envnum = get_envnum(data, "PATH");
	if (envnum == -1)
	{
		p_strct->envpath = NULL;
		return ;
	}
	temp = envp[envnum];
	temp += 5;
	p_strct->envpath = ft_split(temp, ':');
}
