/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:42:12 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/31 15:02:16 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int	handle_close(void)
{
	exit(0);
}

void	player_pos(t_player *player, t_keys key)
{
	if (key == XK_s)
	{
		player->action.up = 0;
		player->action.down = 1;
	}
	else if (key == XK_w)
	{
		player->action.down = 0;
		player->action.up = 1;
	}
	else if (key == XK_a)
	{
		player->action.right = 0;
		player->action.left = 1;
	}
	else if (key == XK_d)
	{
		player->action.left = 0;
		player->action.right = 1;
	}
}

void	player_rot(t_player *player, t_keys key)
{
	if (key == XK_Left)
	{
		player->action.rot_left = 1;
		player->action.rot_right = 0;
	}
	else if (key == XK_Right)
	{
		player->action.rot_right = 1;
		player->action.rot_left = 0;
	}
}

int	key_press(t_keys key, t_player *player)
{
	if (key == XK_escape)
		handle_close();
	player_pos(player, key);
	player_rot(player, key);
	return (0);
}

int	key_release(t_keys key, t_player *player)
{
	if (key == XK_s)
		player->action.down = 0;
	else if (key == XK_w)
		player->action.up = 0;
	else if (key == XK_a)
		player->action.left = 0;
	else if (key == XK_d)
		player->action.right = 0;
	else if (key == XK_Left)
		player->action.rot_left = 0;
	else if (key == XK_Right)
		player->action.rot_right = 0;
	return (0);
}
