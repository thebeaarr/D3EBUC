/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 05:02:08 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/19 17:56:46 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_file	*anode(char *line)
{
	t_file	*node;
	size_t	len;

	node = malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		node->line = ft_substr(line, 0, len - 1);
	else
		node->line = ft_strdup(line);
	if (!node->line)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	add_back(t_file **head, t_file *current)
{
	t_file	*tmp;

	if (!head || !current)
		return ;
	if (!*head)
	{
		*head = current;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = current;
}

bool	isaspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	isspaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isaspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

void	print_error(char *s)
{
	int	i;

	i = ft_strlen(s);
	write(2, s, i);
}
