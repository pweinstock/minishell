/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:34:45 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/01 08:35:33 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_envpath(t_pipex *p_strct, char **envp)
{
	int	i;
	char *temp;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])) != 0)
			break ;
		i++;
	}
	temp = envp[i];
	temp += 5;
	p_strct->envpath = ft_split(temp, ':');
}
