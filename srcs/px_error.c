/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:07:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/29 08:36:21 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_args(t_pipex *p_strct, int argc, char **argv)
{
	int index;
	int cmd_index;

	p_strct->cmd = malloc(sizeof(char *) * (argc + 1));
	p_strct->cmd[argc + 1] = NULL;
	index = 0;
	cmd_index = 0;
	while (index < argc)
	{
		// write(2, argv[index], ft_strlen(argv[index]));
		p_strct->cmd[cmd_index] = ft_split(argv[index], ' ');
		p_strct->cmd_amt++;
		cmd_index++;
		index++;
	}
	printf("cmdamt:%i\n", p_strct->cmd_amt);
	return (0);
}

// static int	open_files(t_data *p_strct, int argc, char **argv)
// {
// 	if (p_strct->fd_in == 0)
// 		p_strct->fd_in = open(argv[1], O_RDONLY);
// 	if (p_strct->fd_out == 0)
// 		p_strct->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	return (0);
// }

int	error_handler(t_pipex *p_strct, int argc, char **argv)
{
	if (argc < 1)
		return (ERROR);
	// if (open_files(p_strct, argc, argv) == ERROR)
	// 	return (ERROR);
	if (parse_args(p_strct, argc, argv) == ERROR)
		return (ERROR);
	return (0);
}
