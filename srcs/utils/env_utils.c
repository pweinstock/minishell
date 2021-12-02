/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:54:54 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/02 12:12:12 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	get_envnum(char **envp, char *needle)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], needle, ft_strlen(envp[i])) != 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**get_envpath(t_pipex *p_strct)
{
	int		envnum;
	char	*temp;

	envnum = get_envnum(p_strct->data->envp, "PATH=");
	if (envnum == -1)
		return (NULL);
	temp = p_strct->data->envp[envnum];
	temp += 5;
	return (ft_split(temp, ':'));
}

void	addback_env(t_pipex *p_strct, char *str)
{
	char	**new;
	int		index;
	int		length;

	length = 0;
	while (p_strct->data->envp[length] != NULL)
		length++;
	new = malloc(sizeof(char *) * length + 2);
	index = 0;
	while (p_strct->data->envp[index] != NULL)
	{
		new[index] = ft_strdup(p_strct->data->envp[index]);
		index++;
	}
	new[index] = ft_strdup(str);
	new[index + 1] = NULL;
	free_envp(p_strct->data);
	p_strct->data->envp = new;
	return ;
}

void	replace_env(t_data *data, char *str, int envnum)
{
	free(data->envp[envnum]);
	data->envp[envnum] = ft_strdup(str);
	return ;
}

void	rotate_env(t_data *data, int envnum)
{
	char	**new;
	int		index;
	int		length;

	length = 0;
	while (data->envp[length] != NULL)
		length++;
	new = malloc(sizeof(char *) * length);
	index = 0;
	length = 0;
	while (data->envp[index] != NULL)
	{
		if (index != envnum)
		{
			new[length] = ft_strdup(data->envp[index]);
			length++;
		}
		index++;
	}
	new[length] = NULL;
	free_envp(data);
	data->envp = new;
	return ;
}
