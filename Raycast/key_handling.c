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
		printf("press s\n");
		player->position.y = 1;
	}
	else if (key == XK_w)
	{
		printf("press w\n");
		player->position.y = -1;
	}
	else if (key == XK_a)
	{
		printf("press a\n");
		player->position.x = -1;
	}
	else if (key == XK_d)
	{
		printf("press d\n");
		player->position.x = 1;
	}
	else if (key == XK_Left)
	{
		player->position.rot_left = 1;
		printf("<-\n");
	}
	else if (key == XK_Right)
	{
		player->position.rot_right = 1; 
		printf("->\n");
	}
	return (0);
}

int	key_release(t_keys key, t_player *player)
{
	if (key == XK_s)
	{
		printf("release s\n");
		player->position.y = 0;
	}
	else if (key == XK_w)
	{
		printf("release w\n");
		player->position.y = 0;
	}
	else if (key == XK_a)
	{
		printf("release a\n");
		player->position.x = 0;
	}
	else if (key == XK_d)
	{
		printf("release d\n");
		player->position.x = 0;
	}
	else if (key == XK_Left)
	{
		player->position.rot_left = 0;
		printf("<-\n");
	}
	else if (key == XK_Right)
	{
		player->position.rot_right = 0;
		printf("->\n");
	}
	return (0);
}

void	update_movement(t_player *player)
{
	if (player->position.x == 1)
		player->position.screen_x += MV_SPEED;
	if (player->position.x == -1)
		player->position.screen_x -= MV_SPEED;
	if (player->position.y == 1)
		player->position.screen_y += MV_SPEED;
	if (player->position.y == -1)
		player->position.screen_y -= MV_SPEED;
	if (player->position.rot_left)
		player->angle -= ROT_SPPED;
	if (player->position.rot_right)
		player->angle += ROT_SPPED;
}
