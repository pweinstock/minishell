/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/25 14:59:32 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	execute(char **input, t_data *data)
{
	t_pipex	p_strct;

	// write(data->original_stdout, ft_itoa(data->fd_in), 1);
	// write(data->original_stdout, "\n", 1);
	// write(data->original_stdout, ft_itoa(data->fd_out), 1);
	// write(data->original_stdout, "\n", 1);
	// if (input[0] != NULL)
	// 	write(data->original_stdout, input[0], ft_strlen(input[0]));
	// write(data->original_stdout, "\n", 1);
	// if (input[1] != NULL)
	// 	write(data->original_stdout, input[1], ft_strlen(input[1]));
	// write(data->original_stdout, "\n", 1);
	// printf("TEST: %s | %s\n", input[0], input[1]);
	signal(SIGINT, SIG_DFL);
	data->is_child = TRUE;
	ft_bzero(&p_strct, sizeof(t_pipex));
	p_strct.cmd = input;
	p_strct.data = data;
	p_strct.envpath = get_envpath(&p_strct);
	if (forking(&p_strct) == ERROR)
		return (1);
	return (0);
}
