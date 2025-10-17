/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:49:25 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/11 19:49:27 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_in_direction(t_player *player, float dir_x, float dir_y)
{
	t_vector_f	new;

	new.x = player->pos.x + dir_x * MV_SPEED;
	new.y = player->pos.y + dir_y * MV_SPEED;
	move_player(player, new);
}

void	update_pos(t_player *player)
{
	if (player->action.up)
	{
		move_in_direction(player, player->dir.x, player->dir.y);
	}
	if (player->action.down)
	{
		move_in_direction(player, -player->dir.x, -player->dir.y);
	}
	if (player->action.left)
	{
		move_in_direction(player, player->dir.y, -player->dir.x);
	}
	if (player->action.right)
	{
		move_in_direction(player, -player->dir.y, player->dir.x);
	}
}

static void	rotate_vector(t_vector_f *vec, float angle)
{
	float	temp;

	temp = vec->x;
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = temp * sin(angle) + vec->y * cos(angle);
}

void	update_rot(t_player *player)
{
	if (player->action.rot_left)
	{
		rotate_vector(&player->dir, -ROT_SPPED);
		rotate_vector(&player->plane, -ROT_SPPED);
	}
	if (player->action.rot_right)
	{
		rotate_vector(&player->dir, ROT_SPPED);
		rotate_vector(&player->plane, ROT_SPPED);
	}
}

/* U don't need to understand this to render textures*/
void	update_transform(t_player *player)
{
	update_pos(player);
	update_rot(player);
}
