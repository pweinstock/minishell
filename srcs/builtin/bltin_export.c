/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:55:01 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 14:12:05 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	addback_env(t_pipex *p_strct, char *str)
{
	int index;

	index = 0;
	while (p_strct->envp[index] != NULL)
		index++;
	p_strct->envp[index] = ft_strdup(str);
	p_strct->envp[index + 1] = malloc(sizeof(char *));
	p_strct->envp[index + 1] = NULL;
	return ;
}

void	bltin_export(t_pipex *p_strct, char **cmd)
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
			addback_env(p_strct, cmd[word_index]);
		word_index++;
	}
	return ;
}
