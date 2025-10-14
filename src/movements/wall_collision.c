/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:52:33 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/11 19:52:38 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	not_wall(t_player *player, float x, float y)
{
	char	**map;

	map = player->data->cub3d->map;
	if (map[(int)floor(y - 0.5)][(int)floor(x - 0.5)] == '1')
		return (0);
	if (map[(int)ceil(y - 0.5)][(int)ceil(x - 0.5)] == '1')
		return (0);
	if (map[(int)floor(y - 0.5)][(int)ceil(x - 0.5)] == '1')
		return (0);
	if (map[(int)ceil(y - 0.5)][(int)floor(x - 0.5)] == '1')
		return (0);
	return (1);
}

void	move_player(t_player *player, t_vector_f new)
{
	if (not_wall(player, new.x, new.y))
	{
		player->pos.x = new.x;
		player->pos.y = new.y;
	}
}
