/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:55:07 by pweinsto          #+#    #+#             */
/*   Updated: 2021/12/01 13:15:27 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lex	*ft_lexnew(char *str, int type)
{
	t_lex	*new_elem;
	char	*token;

	token = str;	new_elem = malloc(sizeof(t_lex));
	if (!new_elem)
		return (0);
	new_elem -> str = token;
	new_elem -> type = type;
	new_elem -> previous = 0;
	new_elem -> next = 0;
	return (new_elem);
}

void	ft_lexadd_back(t_lex *lst, t_lex *new)
{
	t_lex	*save_lst;

	if (!lst)
	{
		lst = new;
		return ;
	}
	save_lst = lst;
	while (lst != 0 && (lst)-> next)
		lst = (lst)-> next;
	(lst)-> next = new;
	new->previous = lst;
	lst = save_lst;
}

void	ft_lexcreate(t_lex **lex, char *str, int type)
{
	t_lex	*element;

	if (*lex == NULL)
		*lex = ft_lexnew(str, type);
	else
	{
		element = ft_lexnew(str, type);
		ft_lexadd_back(*lex, element);
	}
}

int	lex_len(t_lex *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = (lst)-> next;
		i++;
	}
	return (i);
}

void	print_lex(t_lex *lst) //remove!!!
{
	while (lst)
	{
		printf("str: %s\ntype: %d\nprevious: %p\ncurrent: %p\nnext: %p\n\n", (lst)->str, (lst)->type, (lst)->previous, lst, (lst)->next);
		lst = (lst)-> next;
	}
}

int	free_list(t_lex *lst)
{
	t_lex	*next;

	while (lst)
	{
		next = lst->next;
		ft_bzero(lst, sizeof(t_lex));
		free(lst->str);
		free(lst);
		lst = NULL;
		lst = next;
	}
	return (1);
}
