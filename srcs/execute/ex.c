/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/10 17:44:53 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	execute(char **input, t_data *data)
{
	t_pipex	p_strct;

	write(data->original_stdout, ft_itoa(data->fd_in), 1);
	write(data->original_stdout, "\n", 1);
	write(data->original_stdout, ft_itoa(data->fd_out), 1);
	write(data->original_stdout, "\n", 1);
	write(data->original_stdout, input[0], 10);
	write(data->original_stdout, "\n", 1);
	write(data->original_stdout, input[1], 10);
	write(data->original_stdout, "\n", 1);
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
