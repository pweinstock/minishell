/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 14:19:31 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/02 10:01:34 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/minishell.h"

static void	no_nbr(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static int	exit_atoi(char *str)
{
	int		index;
	int		minus;
	long	numb;

	minus = 1;
	index = 0;
	if (str[index] == '-')
		minus = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	numb = 0;
	if (!ft_isdigit(str[index]))
		no_nbr(str);
	while (str[index] >= '0' && str[index] <= '9')
	{
		numb = numb * 10 + str[index] - '0';
		index++;
	}
	if (str[index] != '\0')
		no_nbr(str);
	return ((int)(numb * minus));
}

void	bltin_exit(t_pipex *p_strct, char **cmd)
{
	int	ret;

	ret = 0;
	write(1, "exit\n", 5);
	if (cmd[1] != NULL)
		ret = exit_atoi(cmd[1]);
	free_cmdpath(p_strct);
	p_strct->cmd = NULL;
	free_line(cmd);
	system("leaks minishell");
	exit(ret);
}
