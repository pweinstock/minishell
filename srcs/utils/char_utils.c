/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:16:43 by khirsig           #+#    #+#             */
/*   Updated: 2021/11/18 13:43:11 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chrsrch(char *haystack, char needle)
{
	int index;

	index = 0;
	while (haystack[index] != '\0')
	{
		if (haystack[index] == needle)
			return (index);
		index++;
	}
	return (-1);
}

int	ft_revchrsrch(char *haystack, char needle)
{
	int index;

	index = ft_strlen(haystack);
	while (index >= 0)
	{
		if (haystack[index] == needle)
			return (index);
		index--;
	}
	return (-1);
}

char **ft_strarr_copy(char **str)
{
	char	**new;
	int		index;
	int		length;

	length = 0;
	while (str[length] != NULL)
		length++;
	new = malloc(sizeof(char *) * length + 1);
	index = 0;
	while (str[index] != NULL)
	{
		new[index] = ft_strdup(str[index]);
		index++;
	}
	new[index] = NULL;
	return (new);
}
