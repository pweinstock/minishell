/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:07:41 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/07 09:12:33 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_args(t_pipex *p_strct, char *input)
{
	char **temp;
	int index;
	int cmd_index;
	int pipe_amnt;

	temp = ft_split(input, '|');
	pipe_amnt = 0;
	while (temp[pipe_amnt] != NULL)
		pipe_amnt++;
	if (pipe_amnt < 1)
		return (ERROR);
	p_strct->cmd = malloc(sizeof(char *) * (pipe_amnt + 1));
	p_strct->cmd[pipe_amnt + 1] = NULL;
	index = 0;
	cmd_index = 0;
	while (index < pipe_amnt)
	{
		p_strct->cmd[cmd_index] = ft_split(temp[index], ' ');
		p_strct->cmd_amt++;
		printf("First: |%s|\n", p_strct->cmd[cmd_index][0]);
		cmd_index++;
		index++;
	}
	return (0);
}

int	error_handler(t_pipex *p_strct, char *input)
{
	if (parse_args(p_strct, input) == ERROR)
		return (ERROR);
	return (0);
}
