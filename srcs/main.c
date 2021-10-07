/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/07 10:40:26 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char *shellprefix;
	char *temp;

	data = malloc(sizeof(t_data));
	ft_bzero(data, sizeof(t_data));
	data->envp = envp;
	// data->fd_in = open("fd_in", O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
	//close(data.fd_in);
	// data->fd_out = open("fd_out", O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
	// close(data->fd_out);
	data->fd_in = 0;
	data->fd_out = 1;
	data->path_prefix = ft_strdup("minishell");
	(void)argc;
	(void)argv;
	while (1)
	{
		temp = ft_strjoin("\033[1;32m➜\033[1;36m  ", data->path_prefix);
		shellprefix = ft_strjoin(temp, "\033[1;33m ✗\033[0m ");
		free(temp);
		temp = NULL;
		char	*str = readline(shellprefix);
		free(shellprefix);
		shellprefix = NULL;
		// if (str == NULL)
		// 	break;
		if (str && *str)
			add_history(str);
		pipex(str, envp, data);
		// specifier(&data, str);
		//printf("%s\n", str);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
	}
	// int fd = open("test", O_CREAT);
	// printf("fd: %d\n", fd);
	return (0);
}
