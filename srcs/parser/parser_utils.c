/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:06:02 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/01 13:08:47 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**str_array(t_lex *lst)
{
	char	**line;
	int		i;
	t_lex	*temp;

	while (lst->previous != NULL)
		lst = lst->previous;
	temp = lst;
	line = ft_calloc(lex_len(lst) + 1, sizeof(char **));
	lst = temp;
	i = 0;
	while (lst)
	{
		line[i] = lst->str;
		i++;
		lst = lst->next;
	}
	line[i] = NULL;
	free_list(temp);
	return (line);
}

int	redir_check(t_lex **lex)
{
	*lex = (*lex)->next;
	if (!*lex)
	{
		redir_err(NEWL);
		return (0);
	}
	else if ((*lex)->type != WORD)
	{
		redir_err((*lex)->type);
		return (0);
	}
	return (1);
}

void	redir_err(int type)
{
	write(STDOUT_FILENO, "minishell: syntax error near unexpected token ", 46);
	if (type == OUTPUT)
		write(STDOUT_FILENO, "`>'\n", 4);
	else if (type == APPEND)
		write(STDOUT_FILENO, "`>>'\n", 5);
	else if (type == INPUT)
		write(STDOUT_FILENO, "`>'\n", 4);
	else if (type == HEREDOC)
		write(STDOUT_FILENO, "`<<'\n", 5);
	else if (type == PIPE)
		write(STDOUT_FILENO, "`|'\n", 4);
	else if (type == NEWL)
		write(STDOUT_FILENO, "`newline'\n", 10);
	return ;
}
