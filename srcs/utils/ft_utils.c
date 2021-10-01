/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:08:33 by khirsig           #+#    #+#             */
/*   Updated: 2021/10/01 08:35:41 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(str) + 1;
	while (i < len)
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (!dst)
		return (0);
	while (index < size - 1 && src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	if (size != 0)
		dst[index] = '\0';
	return (ft_strlen(src));
}

void	ft_bzero(void *s, size_t n)
{
	size_t			index;
	unsigned char	*c;

	c = s;
	index = 0;
	while (index < n)
	{
		c[index] = '\0';
		index++;
	}
}
