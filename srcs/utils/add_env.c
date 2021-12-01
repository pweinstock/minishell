/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:01:36 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/01 09:23:53 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	export_str_handling(char *str)
{
	int	index;

	index = 0;
	if (ft_isalpha(str[index]) == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (1);
	}
	while (str[index] != '\0')
	{
		if (str[index] == '=')
			break ;
		if (ft_isalnum(str[index]) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (1);
		}
		index++;
	}
	return (0);
}

int	add_env(t_pipex *p_strct, char *cmd)
{
	char	*temp;
	int		i;
	int		ret;

	ret = 0;
	i = ft_chrsrch(cmd, '=');
	if (export_str_handling(cmd) == 0 && i != -1)
	{
		temp = ft_substr(cmd, 0, i + 1);
		i = get_envnum(p_strct->data->envp, temp);
		free(temp);
		if (i != -1)
			replace_env(p_strct->data, cmd, i);
		else
			addback_env(p_strct, cmd);
	}
	else
		ret = 1;
	return (ret);
}
