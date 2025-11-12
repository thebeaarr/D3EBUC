/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:10 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/12 10:00:46 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

static char get_cell(char **map, int i, int j)
{
    return map[i][j];
}

static bool has_hole(char **map, int i, int j)
{
    if (get_cell(map, i - 1, j) == ' ') return true;
    if (get_cell(map, i + 1, j) == ' ') return true;
    if (get_cell(map, i, j - 1) == ' ') return true;
    if (get_cell(map, i, j + 1) == ' ') return true;
    return false;
}

static bool player_trapped(char **map, int i, int j)
{
    if (get_cell(map, i - 1, j) != '1') return false;
    if (get_cell(map, i + 1, j) != '1') return false;
    if (get_cell(map, i, j - 1) != '1') return false;
    if (get_cell(map, i, j + 1) != '1') return false;
    return true;
}

static bool	check_position(char **map, int i, int j, char c)
{
	if (c == '0' || is_player(c))
	{
		if (has_hole(map, i, j))
		{
			printf("player or zero may escape the map\n");
			return (false);
		}
	}
	if (is_player(c) && player_trapped(map, i, j))
	{
		printf("player can't move\n");
		return (false);
	}
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
