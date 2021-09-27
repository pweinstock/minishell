/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:07:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 15:27:42 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_args(t_data *data, int argc, char **argv)
{
	int index;
	int cmd_index;

	data->cmd = malloc(sizeof(char *) * (argc + 1));
	data->cmd[argc + 1] = NULL;
	index = 0;
	cmd_index = 0;
	while (index < argc)
	{
		data->cmd[cmd_index] = ft_split(argv[index], ' ');
		data->cmd_amt++;
		cmd_index++;
		index++;
	}
	return (0);
}

// static int	open_files(t_data *data, int argc, char **argv)
// {
// 	if (data->fd_in == 0)
// 		data->fd_in = open(argv[1], O_RDONLY);
// 	if (data->fd_out == 0)
// 		data->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	return (0);
// }

int	error_handler(t_data *data, int argc, char **argv)
{
	// if (argc < 5)
	// {
	// 	write(2, "Error: Wrong amount of arguments.\n", 35);
	// 	return (ERROR);
	// }
	// if (open_files(data, argc, argv) == ERROR)
	// 	return (ERROR);
	if (parse_args(data, argc, argv) == ERROR)
		return (ERROR);
	return (0);
}
