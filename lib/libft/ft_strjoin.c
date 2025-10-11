/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:58:13 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/27 19:02:51 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_string = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new_string)
	{
		return (NULL);
	}
	ft_strlcpy(new_string, s1, len_s1 + 1);
	ft_strlcpy(new_string + len_s1, s2, len_s2 + 1);
	return (new_string);
}
