/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 14:19:31 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/04 11:05:05 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	no_nbr(const char *str)
{
	write(2, "minishell: exit: ", 18);
	write(2, &str, ft_strlen(str));
	write(2, ": numeric argument required\n", 29);
	exit(255);
}

static int	exit_atoi(const char *str)
{
	int		count;
	int		minus;
	long	numb;

	minus = 1;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str++;
	count = 0;
	numb = 0;
	if (!ft_isdigit(str[count]))
		no_nbr(str);
	while (str[count] >= '0' && str[count] <= '9')
	{
		numb = numb * 10 + str[count] - '0';
		count++;
	}
	if (str[count] != '\0')
		no_nbr(str);
	return ((int)(numb * minus));
}

void	bltin_exit(t_pipex *p_strct, char **cmd)
{
	int	ret;

	(void)p_strct;
	ret = 0;
	write(1, "exit\n", 5);
	if (cmd[1] != NULL)
		ret = exit_atoi(cmd[1]);
	exit(ret);
}
