/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:20:42 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/10/30 00:52:18 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*e;

	e = malloc(sizeof(t_list));
	if (e)
	{
		e->content = content;
		e->next = NULL;
	}
	return (e);
}
