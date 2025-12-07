/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:54:58 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/20 18:12:54 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	is_empty_line(char *line)
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

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '1' || line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	line_length(char *line)
{
	int	j;

	j = 0;
	while (line[j])
		j++;
	return (j);
}
