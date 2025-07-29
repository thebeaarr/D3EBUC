/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:08:11 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/25 15:31:18 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)(c))
		{
			return ((char *)(s + i));
		}
		i--;
	}
	if (s[0] == (char)(c))
	{
		return ((char *)(s));
	}
	return (NULL);
}
