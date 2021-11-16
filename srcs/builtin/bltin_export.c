/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:55:01 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/15 11:21:03 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	sort_export(char **sort)
{
	char	*temp;
	int		changes;
	int		index;
	int		cmp;

	changes = TRUE;
	while (changes == TRUE)
	{
		index = 0;
		changes = FALSE;
		while (sort[index + 1] != NULL)
		{
			cmp = 0;
			while (sort[index][cmp] == sort[index + 1][cmp])
				cmp++;
			if (sort[index][cmp] > sort[index + 1][cmp])
			{
				temp = sort[index];
				sort[index] = sort[index + 1];
				sort[index + 1] = temp;
				changes = TRUE;
			}
			index++;
		}
	}
}

static void	export_noargs(t_pipex *p_strct, char **cmd)
{
	char	**sort;
	int		count;

	count = 0;
	while (p_strct->data->envp[count] != NULL)
		count++;
	sort = malloc(sizeof(char *) * count + 1);
	count = 0;
	while (p_strct->data->envp[count] != NULL)
	{
		sort[count] = p_strct->data->envp[count];
		count++;
	}
	sort[count] = NULL;
	sort_export(sort);
	count = 0;
	while (sort[count] != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, sort[count], ft_strlen(sort[count]));
		write(1, "\n", 1);
		count++;
	}
	free(sort);
	return ;
}

void	bltin_export(t_pipex *p_strct, char **cmd)
{
	int	word_index;
	int	chr_index;

	word_index = 1;
	chr_index = 0;
	if (cmd[1] == NULL)
	{
		export_noargs(p_strct, cmd);
		return ;
	}
	while (cmd[word_index] != NULL)
	{
		while (cmd[word_index][chr_index] != '=')
			chr_index++;
		if (cmd[word_index][chr_index] != '\0'
			&& cmd[word_index][chr_index + 1] != '\0')
			addback_env(p_strct, cmd[word_index]);
		word_index++;
	}
	return ;
}
