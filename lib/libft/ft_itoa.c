/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:44:41 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/27 20:38:48 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	cg(long c)
{
	size_t	i;

	i = 0;
	if (c == 0)
	{
		return (1);
	}
	while (c > 0)
	{
		i++;
		c /= 10;
	}
	return (i);
}

static char	*create_itoa_string(long a, size_t len, int n)
{
	char	*s;

	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
		s[0] = '-';
	s[len] = '\0';
	while (len > (n < 0))
	{
		s[len - 1] = (a % 10) + '0';
		a /= 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	long	a;
	size_t	len;
	char	*s;

	a = n;
	if (a < 0)
		a = -a;
	len = cg((long)a);
	s = create_itoa_string(a, len + (n < 0), n);
	return (s);
}
