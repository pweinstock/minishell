/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:50:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 17:06:54 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char **str;
	char *ret;
	// char *envp;
	int		count;
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	(void)argv;
	(void)argc;
	//printf("PATH=%s\n", envp);
	while(1)
	{
		ret = readline("\033[1;32m➜\033[1;36m  testshell \033[1;34mgit:(\033[1;31mmaster\033[1;34m)\033[1;33m ✗\033[0m ");
		write(2, "Tes3\n", 6);
		if (strncmp(ret, "Exit", 4) == 0)
			break ;
		if (strncmp(ret, "Fred", 4) == 0)
			write(1, "Das ist unsere Shell.\n", 23);
		// envp = getenv("PATH");
		str = ft_split(ret, '|');
		count = 0;
		while (str[count] != NULL)
			count++;
		data.fd_in = 0;
		data.fd_out = 1;
		if (str[0])
			pipex(count, str, envp, &data);
		write(2, "Test\n", 6);
		// free(ret);
	}
	write(2, "Test\n", 6);
	system("leaks minishell > leaks.txt");
	return (0);
}
