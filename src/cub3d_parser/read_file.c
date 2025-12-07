/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:47:46 by madhat            #+#    #+#             */
/*   Updated: 2025/11/20 18:27:58 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

static bool	read_map(int fd, t_list *list, char *tmp)
{
	t_file	*line;

	if (tmp == NULL)
	{
		print_error("ERROR:incomplete map\n");
		free_list(list);
		return (false);
	}
	list->head_s = anode(tmp);
	free(tmp);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		line = anode(tmp);
		add_back(&list->head_s, line);
		free(tmp);
	}
	return (true);
}

t_list	*read_file(char *path)
{
	t_list *(list);
	char *(tmp);
	int (fd);
	tmp = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_error("ERROR: failed to open file\n");
		return (NULL);
	}
	list = NULL;
	if (!read_config(fd, &list, &tmp))
	{
		close(fd);
		print_error("ERROR: config\n");
		return (NULL);
	}
	if (!read_map(fd, list, tmp))
	{
		print_error("ERROR: map\n");
		close(fd);
		return (NULL);
	}
	close(fd);
	return (list);
}
