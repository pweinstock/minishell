/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:16:43 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/01 08:35:47 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chrsrch(char *haystack, char needle)
{
	int index;

	index = 0;
	while (haystack[index] != '\0')
	{
		// printf("HS: %c ND: %c\n", haystack[index], needle);
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
