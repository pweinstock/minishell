/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:54:54 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 10:58:47 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	get_envnum(char **envp, char *needle)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], needle, ft_strlen(envp[i])) != 0)
			return (i);
		i++;
	}
	return (-1);
}

char **get_envpath(t_pipex *p_strct)
{
	int		envnum;
	char	*temp;

	envnum = get_envnum(p_strct->data->envp, "PATH");
	if (envnum == -1)
		return (NULL);
	temp = p_strct->data->envp[envnum];
	temp += 5;
	return (ft_split(temp, ':'));
}
