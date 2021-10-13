/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:03:38 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/13 15:52:57 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	write(1, " ", 1);
	return ;
}

static void	echo_vars(t_data *data, char *str)
{
	int i;
	int envnum;

	i = 0;
	while (str[i] != '\0')
		i++;
	envnum = get_envnum(data, str + 1);
	if (envnum == -1)
		return ;
	write(1, data->envp[envnum] + i, ft_strlen(data->envp[envnum] + i));
	write(1, " ", 1);
	return ;
}

void	bltin_echo(t_data *data, char **cmd)
{
	int	index;

	index = 1;
	while (cmd[index] != NULL)
	{
		if (cmd[index][0] == '$')
			echo_vars(data, cmd[index]);
		else
			echo_write(cmd[index]);
		index++;
	}
	write(1, "\n", 2);
	return ;
}
