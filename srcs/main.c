/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:45:01 by pweinsto          #+#    #+#             */
/*   Updated: 2021/11/25 16:31:16 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_lex	*lex;
	t_data	data;
	char	*shellprefix;
	char	*temp;
	// char	*str;
	(void)argc;
	(void)argv;
	init_data(&data, envp);
	// stty(&data);
	tcgetattr(STDIN_FILENO, &data.original_attr);
	while (1)
	{
		data.changed_attr = data.original_attr;
		data.changed_attr.c_lflag -= ECHOCTL;
		tcsetattr(STDIN_FILENO , TCSANOW, &data.changed_attr);
		temp = ft_strjoin("\033[1;32m➜\033[1;36m  ", data.path_prefix);
		shellprefix = ft_strjoin(temp, "\033[1;33m ✗\033[0m ");
		free(temp);
		temp = NULL;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		data.str = readline(shellprefix);
		if (!data.str)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (data.str && *data.str)
			add_history(data.str);
		free(shellprefix);
		shellprefix = NULL;
		lex = NULL;
		if (*data.str)
			lex_analyzer(lex, &data);
		// ft_bzero(data.str, ft_strlen(data.str));
		// free(data.str);
		rm(&data);
		data.file_in = NULL;
		data.file_out = NULL;
		data.file = NULL;
	}
	return (0);
}


// two CDQUOTES following