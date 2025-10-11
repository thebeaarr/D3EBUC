/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:45:06 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/11 17:45:07 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(t_data *data, t_player *player, t_vector_f inc, int steps)
{
	t_vector_f	index;
	t_vector	pos;
	int			i;

	i = 0;
	index.x = 0;
	index.y = 0;
	while (i < steps)
	{
		pos.x = (int)(((player->pos.x - 0.5) * TILE) + CENTER + index.x);
		pos.y = 700 + (int)(((player->pos.y - 0.5) * TILE) + CENTER + index.y);
		if (is_border(player->data, pos.x, pos.y))
			break ;
		my_mlx_pixel_put(data->img, pos.x, pos.y, RED);
		index.x += inc.x;
		index.y += inc.y;
		i++;
	}
}

void	player_view(t_player *player)
{
	t_vector	d;
	t_vector_f	inc;
	int			steps;

	d.x = player->dir.x * RAYSIZE;
	d.y = player->dir.y * RAYSIZE;
	if (abs(d.x) > abs(d.y))
		steps = abs(d.x);
	else
		steps = abs(d.y);
	inc.x = (float)d.x / (float)steps;
	inc.y = (float)d.y / (float)steps;
	draw_line(player->data, player, inc, steps);
}
