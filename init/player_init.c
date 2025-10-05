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

#include "cub3d.h"

int	gett_color(char c)
{
	if (c == '1')
		return (WHITE);
	if (c == '0')
		return (BLACK);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (ORANGE);
	return (GREEN);
}

void	player_init(t_player *player)
{
	char		**map;
	int			i;
	int			j;

	map = player->data->cub3d->map;
	player->action.down = 0;
	player->action.up = 0;
	player->action.left = 0;
	player->action.right = 0;
	player->angle = 0;
	i = -1;
	while (map[++i])
	{ 
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (gett_color(map[i][j]) == ORANGE)
			{
				player->pos_x = j * TILE;
				player->pos_y = i * TILE;
				return ;
			}
			j++;
		}
	}
}
