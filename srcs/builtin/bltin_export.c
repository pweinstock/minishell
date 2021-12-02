/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:55:01 by khirsig           #+#    #+#             */
/*   Updated: 2021/12/02 09:33:01 by khirsig          ###   ########.fr       */
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

static void	no_args_print(char *input, int fd)
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
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(before_equal, fd);
	free(before_equal);
	ft_putstr_fd(print, fd);
	free(print);
	ft_putstr_fd("\n", fd);
	return ;
}

static int	export_noargs(t_pipex *p_strct)
{
	char	**sort;
	int		count;

	count = 0;
	while (p_strct->data->envp[count] != NULL)
		count++;
	sort = malloc(sizeof(char *) * count + 1);
	if (sort == NULL)
		return (1);
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
		no_args_print(sort[count], p_strct->data->fd_out);
		count++;
	}
	free(sort);
	return (0);
}

int	bltin_export(t_pipex *p_strct, char **cmd)
{
	int		word_index;
	int		ret;

	word_index = 1;
	ret = 0;
	if (cmd[1] == NULL)
		return (export_noargs(p_strct));
	while (cmd[word_index] != NULL)
	{
		ret = add_env(p_strct, cmd[word_index]);
		word_index++;
	}
	return (ret);
}
