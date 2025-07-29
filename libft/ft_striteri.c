/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:35:43 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/27 20:56:38 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;
	size_t	a;

	i = 0;
	if (!s)
		return ;
	a = ft_strlen(s);
	while (i < a)
	{
		(*f)(i, s + i);
		i++;
	}
}
