/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:03:17 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/23 21:00:50 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*q;
	const unsigned char	*p;

	p = s1;
	q = s2;
	while (n > 0)
	{
		if (*p != *q)
		{
			return (*p - *q);
		}
		p++;
		q++;
		n--;
	}
	return (0);
}
