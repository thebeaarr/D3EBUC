/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:20:17 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/11/02 22:54:42 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = *lst;
	if (!new)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new;
	}
}
