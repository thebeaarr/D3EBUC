/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:42:12 by sel-jari          #+#    #+#             */
/*   Updated: 2025/09/18 00:42:26 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(void)
{
	printf("cub3D closed\n");
	exit(1);
}

int	key_press(t_keys key, t_player *player)
{
	if (key == XK_escape)
	{
		printf("cub3D closed(Esc)\n");
	//   free_all_exit()
		exit(0);
	}
	else if (key == XK_s)
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
	else if (key == XK_Left)
	{
		player->action.rot_left = 1;
		player->action.rot_right= 0;
	}
	else if (key == XK_Right)
	{
		player->action.rot_right = 1; 
		player->action.rot_left = 0; 
	}
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

void	update_movement(t_player *player)
{
	if (player->action.right)
	{
		player->action.screen_x += cosf(M_PI_2 + player->angle) * MV_SPEED;
		player->action.screen_y += sin(M_PI_2 + player->angle) * MV_SPEED;
	}
	if (player->action.left)
	{
		player->action.screen_x += cosf(-M_PI_2 + player->angle) * MV_SPEED;
		player->action.screen_y += sin(-M_PI_2 + player->angle) * MV_SPEED;
	}
	if (player->action.down)
	{
		player->action.screen_x -= cosf(player->angle) * MV_SPEED;
		player->action.screen_y -= sin(player->angle) * MV_SPEED;
	}
	if (player->action.up)
	{
		player->action.screen_x += cosf(player->angle) * MV_SPEED;
		player->action.screen_y += sin(player->angle) * MV_SPEED;
	}
	if (player->action.rot_left)
	{
		player->angle -= ROT_SPPED;
	}
	if (player->action.rot_right)
	{
		player->angle += ROT_SPPED;
	}
}
