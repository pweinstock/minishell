/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:29:30 by pweinsto          #+#    #+#             */
/*   Updated: 2021/10/09 18:40:29 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output(t_data *data, char *str)
{
	// char	*buf;
	// char	*str = "12345678";

	// write(data->fd_in, str, ft_strlen(str));
	// close(data->fd_in);
	// buf = malloc(sizeof(char) * ft_strlen(str) + 1);
	// data->fd_in = open("fd_in", O_RDWR);
	// read(data->fd_in, buf, ft_strlen(str)); // write a function for size
	// close(data->fd_in);
	// data->fd_out = open(file, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	// write(data->fd_out, buf, ft_strlen(str));
	// close(data->fd_out);
	char	*file;
	
	while (str[data->i] == ' ' || str[data->i] == '|')
			data->i++;
	data->cmd = ft_substr(str, data->i, data->j - data->i - 1);
	data->j += 1;
	while (str[data->j] == ' ')
		data->j++;
	data->i = data->j;
	while (str[data->j] != ' ' && str[data->j] != '\0')
		data->j++;
	file = ft_substr(str, data->i, data->j - data->i);
	data->fd_out = open(file, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	pipex(data->cmd, data->envp, data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	//close(data->fd_in);
	close(data->fd_out);
	//dup2(data->fd_out, data->fd_in); 
	data->fd_in = data->fd_out;
	//data->fd_out = 1;
	data->j -= 1;
	data->i = data->j;
	data->i += 1;
}

void	output_append(t_data *data, char *str)
{
	char	*file;
	
	while (str[data->i] == ' ' || str[data->i] == '|')
			data->i++;
	data->cmd = ft_substr(str, data->i, data->j - data->i - 1);
	data->j += 2;
	while (str[data->j] == ' ')
		data->j++;
	data->i = data->j;
	while (str[data->j] != ' ' && str[data->j] != '\0')
		data->j++;
	file = ft_substr(str, data->i, data->j - data->i);
	data->fd_out = open(file, O_CREAT|O_RDWR|O_APPEND, S_IRWXU);
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	pipex(data->cmd, data->envp, data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->fd_in);
	close(data->fd_out);
	data->fd_in = data->fd_out;
	data->fd_out = 1;
	data->j -= 1;
	data->i = data->j;
	data->i += 1;
// 	char	*buf;
// 	char	*str = "abcdefgh";

// 	write(data->fd_in, str, ft_strlen(str));
// 	close(data->fd_in);
// 	buf = malloc(sizeof(char) * ft_strlen(str));
// 	data->fd_in = open("fd_in", O_RDWR);
// 	read(data->fd_in, buf, ft_strlen(str)); // write a function for size
// 	close(data->fd_in);
// 	data->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
// 	write(data->fd_out, buf, ft_strlen(str));
// 	close(data->fd_out);
}

void	input(t_data *data, char *str)
{
	char	*file;


	while (str[data->i] == ' ' || str[data->i] == '|')
			data->i++;
	data->cmd = ft_substr(str, data->i, data->j - data->i - 1);
	data->j += 1;
	while (str[data->j] == ' ')
		data->j++;
	data->i = data->j;
	while (str[data->j] != ' ' && str[data->j] != '\0')
		data->j++;
	file = ft_substr(str, data->i, data->j - data->i);
	data->fd_in = open(file, O_RDONLY, S_IRWXU);
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	pipex(data->cmd, data->envp, data);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->fd_in);
	close(data->fd_out);
	data->fd_in = 0;
	data->fd_out = 1;
	data->j -= 1;
	data->i = data->j;
	data->i += 1;
// 	buf = malloc(sizeof(char) * 4);
// 	//buf[3] = '\0';
// 	data->fd_in = open(file, O_RDONLY);
// 	read(data->fd_in, buf, 4); // write a function for size
// 	close(data->fd_in);
// 	data->fd_out = open("fd_out", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
// 	write(data->fd_out, buf, 4);
// 	close(data->fd_out);

}

// void	input_append(t_data *data, char *str)
// {
// 	data->fd_out = open("fd_out", O_RDWR | O_APPEND, S_IRWXU);
// 	while (1)
// 	{
// 		char	*str = readline("heredoc> ");
// 		if (!ft_strncmp(delimiter, str, ft_strlen(str)) && str[0] != 0)
// 			break;
// 		write(data->fd_out, str, ft_strlen(str));
// 		write(data->fd_out, "\n", 1);
// 	}
// 	close(data->fd_out);
//}