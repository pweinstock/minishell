/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khirsig <khirsig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:50:51 by khirsig           #+#    #+#             */
/*   Updated: 2021/09/27 17:03:28 by khirsig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_string;
	unsigned int	index;
	unsigned int	length;

	if (!s1 || !s2)
		return (0);
	length = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(length + 1);
	if (!new_string)
		return (0);
	index = 0;
	while (index < length && s1[index] != '\0')
	{
		new_string[index] = s1[index];
		index++;
	}
	while (index < length && s2[index - ft_strlen(s1)] != '\0')
	{
		new_string[index] = s2[index - ft_strlen(s1)];
		index++;
	}
	new_string[index] = '\0';
	return (new_string);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!ft_strlen(needle))
		return ((char *) haystack);
	while (i < len && haystack[i] != 0)
	{
		j = 0;
		while (needle[j] == haystack[i + j]
			&& haystack[i + j] != '\0' && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	while (!(!s) && s[index] != '\0')
	{
		write(fd, &s[index], 1);
		index++;
	}
}

char	*ft_strdup(const char *src)
{
	char	*dst;

	dst = malloc(ft_strlen (src) + 1);
	if (dst == 0)
		return (0);
	ft_strlcpy (dst, src, ft_strlen(src) + 1);
	return (dst);
}
