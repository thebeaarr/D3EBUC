/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:41:00 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/20 17:00:30 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	skip_leading_spaces(char *line)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	return (i);
}

static t_list	*init_list(t_file *line)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head_f = line;
	list->head_s = NULL;
	return (list);
}

void	store_config_line(char *tmp, t_list **list)
{
	int		i;
	t_file	*line;

	i = skip_leading_spaces(tmp);
	line = anode(tmp + i);
	if (!*list)
		*list = init_list(line);
	else
		add_back(&(*list)->head_f, line);
}

bool	valid_before_map(char *tmp, t_list **list, int fd)
{
	int	size;

	if (!is_map_line(tmp))
		return (true);
	if (!*list)
	{
		free_gnl(tmp, fd);
		return (false);
	}
	size = size_list((*list)->head_f);
	if (size != 6)
	{
		free_gnl(tmp, fd);
		free_list(*list);
		return (false);
	}
	return (true);
}

bool	read_config(int fd, t_list **list, char **tmp)
{
	while (1)
	{
		*tmp = get_next_line(fd);
		if (!*tmp)
			break ;
		if (is_empty_line(*tmp))
		{
			free(*tmp);
			continue ;
		}
		if (is_map_line(*tmp))
			break ;
		store_config_line(*tmp, list);
		free(*tmp);
	}
	if (!valid_before_map(*tmp, list, fd))
		return (false);
	if (size_list((*list)->head_f) != 6)
		return (false);
	return (true);
}
