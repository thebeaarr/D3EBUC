/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:31:23 by madhat            #+#    #+#             */
/*   Updated: 2025/11/17 16:41:55 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	dup_(t_file *ca)
{
	t_file	*c;
	int		check;

	int (w), (e), (s), (n);
	w = 0;
	e = 0;
	s = 0;
	n = 0;
	c = ca;
	while (c)
	{
		check = is_txt(c->line);
		if (check == 1)
			n++;
		else if (check == 2)
			s++;
		else if (check == 3)
			w++;
		else if (check == 4)
			e++;
		if (e > 1 || w > 1 || s > 1 || n > 1)
			return (true);
		c = c->next;
	}
	return (!(e == 1 && w == 1 && s == 1 && n == 1));
}

static bool	validate_texture(char **texture)
{
	if (!check_ntxt(texture))
		return (false);
	if (!path_valid(texture[1]))
		return (false);
	return (true);
}

static bool	process_texture_line(char ***textures, char *line, int *count)
{
	if (!is_txt(line))
		return (true);
	textures[*count] = ft_split_space(line);
	if (!validate_texture(textures[*count]))
	{
		printf("ERROR: invalid texture path\n");
		free_tptr(textures, *count);
		return (false);
	}
	(*count)++;
	return (true);
}

static char	***allocate_textures(void)
{
	char	***textures;

	textures = malloc(sizeof(char **) * 5);
	if (!textures)
		return (NULL);
	textures[4] = NULL;
	return (textures);
}

char	***get_textures(t_file *head)
{
	t_file	*current;
	char	***textures;
	int		count;

	if (dup_(head))
	{
		printf("ERROR:duplicated textures/not enough texture!\n");
		return (NULL);
	}
	textures = allocate_textures();
	if (!textures)
		return (NULL);
	current = head;
	count = 0;
	while (current && count < 4)
	{
		if (!process_texture_line(textures, current->line, &count))
			return (NULL);
		current = current->next;
	}
	return (textures);
}
