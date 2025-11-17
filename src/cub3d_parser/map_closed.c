/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:10 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/12 10:39:39 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

bool	has_hole(char **map, int i, int j)
{
	if (map[i - 1][j] == ' ')
		return (true);
	if (map[i + 1][j] == ' ')
		return (true);
	if (map[i][j - 1] == ' ')
		return (true);
	if (map[i][j + 1] == ' ')
		return (true);
	return (false);
}

bool	player_trapped(char **map, int i, int j)
{
	if (map[i - 1][j] != '1')
		return (false);
	if (map[i + 1][j] != '1')
		return (false);
	if (map[i][j - 1] != '1')
		return (false);
	if (map[i][j + 1] != '1')
		return (false);
	return (true);
}

static bool	check_line(char **map, int i)
{
	int		j;
	char	c;

	j = 0;
	while (map[i][j])
	{
		c = map[i][j];
		if (!check_position(map, i, j, c))
			return (false);
		j++;
	}
	return (true);
}

bool	map_closed(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!check_line(map, i))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_map(char **map)
{
	int	player_count;
	int	i;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		if (!check_line_chars(map[i], &player_count))
			return (false);
		if (!line_has_walls(map[i]))
			return (false);
		i++;
	}
	if (!c_player(player_count) || !map_closed(map))
		return (false);
	return (true);
}
