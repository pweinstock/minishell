/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/05 15:46:45 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	execute(char **input, t_data *data)
{
	t_pipex	p_strct;

	ft_bzero(&p_strct, sizeof(t_pipex));
	p_strct.cmd = input;
	p_strct.data = data;
	p_strct.envpath = get_envpath(&p_strct);
	if (forking(&p_strct) == ERROR)
		return (1);
	free(p_strct.cmd);
	p_strct.cmd = NULL;
	return (0);
}
