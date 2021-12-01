/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/01 13:11:59 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	free_line(char **line)
{
	char	**temp;

	temp = line;
	while (*line)
	{
		free(*line);
		*line = NULL;
		line++;
	}
	free(*line);
	*line = NULL;
	free(temp);
	return (1);
}

int	execute(char **input, t_data *data)
{
	t_pipex	p_strct;

	data->is_child = TRUE;
	ft_bzero(&p_strct, sizeof(t_pipex));
	p_strct.cmd = input;
	p_strct.data = data;
	p_strct.envpath = get_envpath(&p_strct);
	if (forking(&p_strct) == ERROR)
	{
		free_line(input);
		return (1);
	}
	free_line(input);
	return (0);
}
