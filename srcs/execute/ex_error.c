/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:07:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/02 13:57:09 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	parse_args(t_pipex *p_strct, char *input)
// {
// 	char **temp;
// 	int index;
// 	int cmd_index;
// 	int pipe_amnt;

// 	temp = ft_split(input, '|');
// 	pipe_amnt = 0;
// 	while (temp[pipe_amnt] != NULL)
// 		pipe_amnt++;
// 	if (pipe_amnt < 1)
// 		return (ERROR);
// 	p_strct->cmd = malloc(sizeof(char *) * (pipe_amnt + 1));
// 	p_strct->cmd[pipe_amnt] = NULL;
// 	index = 0;
// 	cmd_index = 0;
// 	while (index < pipe_amnt)
// 	{
// 		p_strct->cmd[cmd_index] = split_args(temp[index]);
// 		p_strct->cmd_amt++;
// 		cmd_index++;
// 		index++;
// 	}
// 	return (0);
// }

// int	error_handler(t_pipex *p_strct, char *input)
// {
// 	if (parse_args(p_strct, input) == ERROR)
// 		return (ERROR);
// 	return (0);
// }
