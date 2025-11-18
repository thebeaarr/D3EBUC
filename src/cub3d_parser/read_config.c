/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:41:00 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/17 21:28:59 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isspace(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '1' || line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

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

void free_gnl(char *line , int fd)
{
	if (line)
		free(line);
	while((line = get_next_line(fd)))
		free(line);
	close(fd);
}

bool	read_config(int fd, t_list **list, char **tmp)
{
	t_file *(line);
	int (i);
	while ((*tmp = get_next_line(fd)))
	{
		if (is_empty_line(*tmp))
		{
			free(*tmp);
			continue ;
		}
		if (is_map_line(*tmp))
			break ;
		i = skip_leading_spaces(*tmp);
		line = anode(*tmp + i);
		if (!*list)
			*list = init_list(line);
		else
			add_back(&(*list)->head_f, line);
		free(*tmp);
	}
	if (size_list((*list)->head_f) != 6)
	{
		print_error("ERROR: too much config lines\n");
		free_gnl(*tmp , fd);
		free_list(*list);
		return (false);
	}
	return (true);
}
