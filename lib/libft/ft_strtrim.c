/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:32:29 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/27 21:07:58 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(int c, const char *set)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*new_string;

	if (!s1 && !set)
		return (NULL);
	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && in_set(s1[start], set))
		start++;
	while (end > start && in_set(s1[end - 1], set))
		end--;
	new_string = malloc(sizeof(char) * (end - start + 1));
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1 + start, end - start + 1);
	return (new_string);
}
