/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:55:01 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 12:41:16 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

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
