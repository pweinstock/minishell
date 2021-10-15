/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:55:01 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/14 13:18:42 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	addback_env(t_data *data, char *str)
{
	int index;

	index = 0;
	while (data->envp[index] != NULL)
		index++;
	data->envp[index] = ft_strdup(str);
	data->envp[index + 1] = malloc(sizeof(char *));
	data->envp[index + 1] = NULL;
	return ;
}

void	bltin_export(t_data *data, char **cmd)
{
	int word_index;
	int	chr_index;

	word_index = 1;
	chr_index = 0;
	while (cmd[word_index] != NULL)
	{
		while (cmd[word_index][chr_index] != '=')
			chr_index++;
		if (cmd[word_index][chr_index] != '\0' && cmd[word_index][chr_index + 1] != '\0')
			addback_env(data, cmd[word_index]);
		word_index++;
	}
	return ;
}
