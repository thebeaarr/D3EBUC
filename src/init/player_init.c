/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:40:27 by sel-jari          #+#    #+#             */
/*   Updated: 2025/09/18 00:40:29 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_tile_color(char c)
{
	if (c == '1')
		return (BLACK);
	if (c == '0')
		return (FLOOR);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (ORANGE);
	return (BLACK);
}

static void	set_direction(t_player *player, t_vector_f plane, t_vector_f dir)
{
	player->plane = plane;
	player->dir = dir;
}

void	set_player_direction(t_player *player, char c)
{
	if (c == 'N')
		set_direction(player, (t_vector_f){0.65, 0}, (t_vector_f){0, -1});
	else if (c == 'E')
		set_direction(player, (t_vector_f){0, 0.65}, (t_vector_f){1, 0});
	else if (c == 'S')
		set_direction(player, (t_vector_f){-0.65, 0}, (t_vector_f){0, 1});
	else if (c == 'W')
		set_direction(player, (t_vector_f){0, -0.65}, (t_vector_f){-1, 0});
}

t_vector_f	set_player_pos(char **map)
{
	int			i;
	int			j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] > '1')
				return ((t_vector_f){j + 0.5, i + 0.5});
			j++;
		}
		i++;
	}
	return ((t_vector_f){0, 0});
}

void	player_init(t_player *player)
{
	char		**map;

	map = player->data->cub3d->map;
	player->action.down = 0;
	player->action.up = 0;
	player->action.left = 0;
	player->action.right = 0;
	player->angle = 0;
	player->pos = set_player_pos(map);
	player->data->init_pos = player->pos;
	player->data->mmap.pos.x = 0;
	player->data->mmap.pos.y = 0;
	set_player_direction(player, map[(int)player->pos.y][(int)player->pos.x]);
}
