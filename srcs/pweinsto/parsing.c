/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:44:43 by pweinsto          #+#    #+#             */
/*   Updated: 2021/10/09 16:34:42 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	specifier(t_data *data, char *str)
{
	//char	*file;

	data->i = 0;
	data->j = 0;
	while (str[data->j])
	{
		if (str[data->j] == '>' && str[data->j + 1] == '>')
			output_append(data, str);
		else if (str[data->j] == '>')
			output(data, str);
		
		else if (str[data->j] == '<')
			input(data, str);
		data->j++;
	}
	if ((data->j - data->i) >= 2)
	{
		
		while (str[data->i] == ' ' || str[data->i] == '|')
			data->i++;
		data->cmd = ft_substr(str, data->i, data->j - data->i);
		// printf("cmd: %s\n", data->cmd);
		// printf("in: %d | out: %d\n", data->fd_in, data->fd_out);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		pipex(data->cmd, data->envp, data);
		dup2(data->original_stdin, STDIN_FILENO);
		dup2(data->original_stdout, STDOUT_FILENO);
		// close(data->fd_in);
		// close(data->fd_out); 
		//write(1, "x", 1);
	}
	data->cmd = NULL;
	data->i = 0;
	data->j = 0;	
	// data->cmd = ft_substr(str, data->i, data->j - data->i - 1);
	// data->j += 1;
	// while (str[data->j] == ' ')
	// 	data->j++;
	// data->i = data->j;
	// while (str[data->j] != ' ')
	// 	data->j++;
	// file = ft_substr(str, data->i, data->j - data->i);
	// data->fd_out = open(file, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	// pipex(data->cmd, data->envp, data);
	//output(vars, str);
	//output_append(vars, str);
	// input(vars, str);
	//input_append(vars, str);
}