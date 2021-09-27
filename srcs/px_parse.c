/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:34:45 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 15:16:29 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_envpath(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])) != 0)
			break ;
		i++;
	}
	envp[i] += 5;
	data->envpath = ft_split(envp[i], ':');
}
