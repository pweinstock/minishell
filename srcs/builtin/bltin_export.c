/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:55:01 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/24 10:37:20 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	sort_export(char **sort)
{
	char	*temp;
	int		changes;
	int		index;
	int		cmp;

	changes = TRUE;
	while (changes == TRUE)
	{
		index = 0;
		changes = FALSE;
		while (sort[index + 1] != NULL)
		{
			cmp = 0;
			while (sort[index][cmp] == sort[index + 1][cmp])
				cmp++;
			if (sort[index][cmp] > sort[index + 1][cmp])
			{
				temp = sort[index];
				sort[index] = sort[index + 1];
				sort[index + 1] = temp;
				changes = TRUE;
			}
			index++;
		}
	}
}

static void	no_args_print(char *input)
{
	char	*before_equal;
	char	*after_equal;
	char	*print;
	char	*temp;
	int		equal_sign;

	equal_sign = ft_chrsrch(input, '=');
	if (equal_sign == -1)
		equal_sign = ft_strlen(input);
	before_equal = ft_substr(input, 0, equal_sign + 1);
	after_equal = ft_substr(input, equal_sign + 1, ft_strlen(input));
	temp = ft_strjoin("\"", after_equal);
	free(after_equal);
	print = ft_strjoin(temp, "\"");
	free(temp);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(before_equal, 1);
	free(before_equal);
	ft_putstr_fd(print, 1);
	free(print);
	ft_putstr_fd("\n", 1);
	return ;
}

static void	export_noargs(t_pipex *p_strct, char **cmd)
{
	char	**sort;
	int		count;

	count = 0;
	while (p_strct->data->envp[count] != NULL)
		count++;
	sort = malloc(sizeof(char *) * count + 1);
	count = 0;
	while (p_strct->data->envp[count] != NULL)
	{
		sort[count] = p_strct->data->envp[count];
		count++;
	}
	sort[count] = NULL;
	sort_export(sort);
	count = 0;
	while (sort[count] != NULL)
	{
		no_args_print(sort[count]);
		count++;
	}
	free(sort);
	return ;
}

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

int	bltin_export(t_pipex *p_strct, char **cmd)
{
	char	*temp;
	int		word_index;
	int		i;
	int		ret;

	word_index = 1;
	ret = 0;
	if (cmd[1] == NULL)
	{
		export_noargs(p_strct, cmd);
		return (ret);
	}
	while (cmd[word_index] != NULL)
	{
		i = ft_chrsrch(cmd[word_index], '=');
		if (export_str_handling(cmd[word_index]) == 0 && i != -1)
		{
			temp = ft_substr(cmd[word_index], 0, i + 1);
			i = get_envnum(p_strct->data->envp, temp);
			if (i != -1)
				replace_env(p_strct->data, cmd[word_index], i);
			else
				addback_env(p_strct, cmd[word_index]);
		}
		else
			ret = 1;
		word_index++;
	}
	return (ret);
}
