/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:45:01 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/05 20:15:18 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_lex	*lex;
	t_data	data;
	char	*shellprefix;
	char	*temp;
	char	*str;


	(void)argc;
	(void)argv;
	init_data(&data, envp);
	while (1)
	{
		data.fd_in = 0;
		data.fd_out = 1;
		temp = ft_strjoin("\033[1;32m➜\033[1;36m  ", data.path_prefix);
		shellprefix = ft_strjoin(temp, "\033[1;33m ✗\033[0m ");
		free(temp);
		temp = NULL;

		str = readline(shellprefix);
		if (str && *str)
			add_history(str);
		free(shellprefix);
		shellprefix = NULL;
		lex = NULL;
		lex_analyzer(lex, str, &data);
		rm(&data);
		data.file_in = NULL;
		data.file_out = NULL;
		data.file = NULL;
	}
	return (0);
}


// two CDQUOTES following