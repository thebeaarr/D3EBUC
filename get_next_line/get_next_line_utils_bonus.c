/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:44:27 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/11/30 18:44:28 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr)
		ft_memset(ptr, 0, count * size);
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;

	i = merging(s1, 1);
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s1, (i + 1));
	return (p);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = merging(src, 1);
	i = 0;
	if (dstsize == 0)
	{
		return (j);
	}
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_string;

	if (!s1 && !s2)
	{
		return (NULL);
	}
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len_s1 = merging(s1, 1);
	len_s2 = merging(s2, 1);
	new_string = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new_string)
	{
		return (NULL);
	}
	ft_strlcpy(new_string, s1, len_s1 + 1);
	ft_strlcpy(new_string + len_s1, s2, len_s2 + 1);
	return (new_string);
}
