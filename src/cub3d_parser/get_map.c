/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:04 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/12 10:31:04 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

static int	get_max_length(t_file *head)
{
	t_file	*current;
	int		max;
	int		len;

	max = 0;
	current = head;
	while (current)
	{
		len = ft_strlen(current->line);
		if (len > max)
			max = len;
		current = current->next;
	}
	return (max);
}

static int	count_lines(t_file *head)
{
	t_file	*current;
	int		count;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	fill_line(char *dest, char *src, int max)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	while (j < max)
	{
		dest[j] = ' ';
		j++;
	}
	dest[j] = '\0';
}

char	**get_map(t_file *head)
{
	t_file	*current;
	char	**map;
	int		max;
	int		i;

	max = get_max_length(head);
	i = count_lines(head);
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (NULL);
	map[i] = NULL;
	current = head;
	i = 0;
	while (current)
	{
		map[i] = malloc(sizeof(char) * (max + 1));
		if (!map[i])
			return (NULL);
		fill_line(map[i], current->line, max);
		current = current->next;
		i++;
	}
	return (map);
}
