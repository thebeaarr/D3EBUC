/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:01 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/19 18:13:40 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*rm_spaces_check(char *s)
{
	char	*new;
	int		t;
	int		index;
	int		virgule ;

	t = 0;
	index = 0;
	virgule = 0;
	while (s[index])
	{
		if (s[index] == ',')
			virgule++;
		if (virgule > 2)
			return (NULL);
		index++;
	}
	index = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (s[0] == 'C' || s[0] == 'F')
		index = 1;
	while (s[index] && isspace(s[index]))
		index++;
	while (s[index])
	{
		new[t] = s[index];
		t++;
		index++;
	}
	new[t] = '\0';
	return (new);
}

static int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (isspace(str[i]))
		i++;
	return (i);
}

static bool	is_color_line(char *line, char type)
{
	int	index;

	index = skip_spaces(line);
	if (!strncmp(&type, line + index, 1) && isspace(line[index + 1]))
		return (true);
	return (false);
}

static void	parse_colors(t_cub3d *store, t_file *head)
{
	t_file	*current;
	char	*tmp;
	int		index;

	current = head;
	while (current)
	{
		tmp = current->line;
		index = skip_spaces(tmp);
		if (is_color_line(tmp, 'F'))
			store->floor = get_color(tmp + index);
		else if (is_color_line(tmp, 'C'))
			store->ceiling = get_color(tmp + index);
		current = current->next;
	}
}

bool	get_colors_(t_cub3d *store, t_file *head)
{
	if (dup_c(head))
	{
		print_error("ERROR: duplicated colors\n");
		return (false);
	}
	store->ceiling = -1;
	store->floor = -1;
	parse_colors(store, head);
	if (store->ceiling == -1 || store->floor == -1)
	{
		print_error("ERROR: invalid color values\n");
		return (false);
	}
	return (true);
}
