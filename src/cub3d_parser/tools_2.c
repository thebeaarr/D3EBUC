/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:21 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/17 21:26:18 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	size_list(t_file *head)
{
	t_file	*current;
	int		size;

	current = head;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

void	free_file(t_file *head)
{
	t_file	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->line);
		free(head);
		head = tmp;
	}
}

void	free_list(t_list *head)
{
	if (head)
	{
		if(head->head_f)
			free_file(head->head_f);
		if(head->head_s)
			free_file(head->head_s);
		free(head);
	}
}

void print_error(char *s)
{
	write(2 , s, ft_strlen(s));
}
