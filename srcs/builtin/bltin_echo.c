/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:03:38 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 11:00:23 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	echo_write(char *str)
{
	int index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] != '\\' && str[index - 1] != '\\')
			write(1, &str[index], 1);
		index++;
	}
	return ;
}

static void	echo_vars(t_pipex *p_strct, char *str)
{
	int i;
	int envnum;

	i = 0;
	while (str[i] != '\0')
		i++;
	envnum = get_envnum(p_strct->data->envp, str + 1);
	if (envnum == -1)
		return ;
	write(1, p_strct->data->envp[envnum] + i, ft_strlen(p_strct->data->envp[envnum] + i));
	return ;
}

void	bltin_echo(t_pipex *p_strct, char **cmd)
{
	int	index;
	int	flag;

	flag = FALSE;
	index = 1;
	if (ft_strnstr(cmd[1], "-n", 2) != 0)
	{
		flag = TRUE;
		index = 2;
	}
	while (cmd[index] != NULL)
	{
		if (cmd[index][0] == '$')
			echo_vars(p_strct, cmd[index]);
		else
			echo_write(cmd[index]);
		if (cmd[index + 1] != NULL)
			write(1, " ", 1);
		index++;
	}
	if (flag == TRUE )
		return ;
	write(1, "\n", 1);
	return ;
}
