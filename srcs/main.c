/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:45:01 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/04 10:24:23 by khirsig          ###   ########.fr       */
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

	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	data.path_prefix = ft_strdup("minishell");
	data.fd_in = STDIN_FILENO;
	data.fd_out = STDOUT_FILENO;
	(void)argc;
	(void)argv;
	data.envp = envp;
	while (1)
	{
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

	}
	return (0);
}


// two CDQUOTES following