/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:52:33 by sel-jari          #+#    #+#             */
/*   Updated: 2025/11/19 20:09:27 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static	int	not_wall(t_data *data, float x, float y)
{
	return (data->cub3d->map[(int)y][(int)x] != '1');
}

void	move_player(t_player *player, t_vector_f new)
{
	if (not_wall(player->data, new.x, player->pos.y))
		player->pos.x = new.x;
	if (not_wall(player->data, player->pos.x, new.y))
		player->pos.y = new.y;
}
