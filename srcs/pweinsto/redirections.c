/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:29:30 by pweinsto          #+#    #+#             */
/*   Updated: 2021/10/07 09:59:13 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	output(t_struct *vars, char *file)
// {
// 	char	*buf;
// 	char	*str = "12345678";

// 	write(vars->fd_in, str, ft_strlen(str));
// 	close(vars->fd_in);
// 	buf = malloc(sizeof(char) * ft_strlen(str) + 1);
// 	vars->fd_in = open("fd_in", O_RDWR);
// 	read(vars->fd_in, buf, ft_strlen(str)); // write a function for size
// 	close(vars->fd_in);
// 	vars->fd_out = open(file, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
// 	write(vars->fd_out, buf, ft_strlen(str));
// 	close(vars->fd_out);
// }

// void	output_append(t_struct *vars, char *file)
// {
// 	char	*buf;
// 	char	*str = "abcdefgh";

// 	write(vars->fd_in, str, ft_strlen(str));
// 	close(vars->fd_in);
// 	buf = malloc(sizeof(char) * ft_strlen(str));
// 	vars->fd_in = open("fd_in", O_RDWR);
// 	read(vars->fd_in, buf, ft_strlen(str)); // write a function for size
// 	close(vars->fd_in);
// 	vars->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
// 	write(vars->fd_out, buf, ft_strlen(str));
// 	close(vars->fd_out);
// }

// void	input(t_struct *vars, char *file)
// {
// 	char	*buf;

// 	buf = malloc(sizeof(char) * 4);
// 	//buf[3] = '\0';
// 	vars->fd_in = open(file, O_RDONLY);
// 	read(vars->fd_in, buf, 4); // write a function for size
// 	close(vars->fd_in);
// 	vars->fd_out = open("fd_out", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
// 	write(vars->fd_out, buf, 4);
// 	close(vars->fd_out);

// }

// void	input_append(t_struct *vars, char *delimiter)
// {
// 	vars->fd_out = open("fd_out", O_RDWR | O_APPEND, S_IRWXU);
// 	while (1)
// 	{
// 		char	*str = readline("heredoc> ");
// 		if (!ft_strncmp(delimiter, str, ft_strlen(str)) && str[0] != 0)
// 			break;
// 		write(vars->fd_out, str, ft_strlen(str));
// 		write(vars->fd_out, "\n", 1);
// 	}
// 	close(vars->fd_out);
// }