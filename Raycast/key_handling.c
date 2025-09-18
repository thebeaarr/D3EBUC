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

int	key_press(t_keys key, t_data *data)
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
		data->position.y += 1;
	}
	else if (key == XK_w)
	{
		printf("press w\n");
		data->position.y -= 1;
	}
	else if (key == XK_a)
	{
		printf("press a\n");
		data->position.x -= 1;
	}
	else if (key == XK_d)
	{
		printf("press d\n");
		data->position.x += 1;
	}
	else if (key == XK_Left)
		printf("<-\n");
	else if (key == XK_Right)
		printf("->\n");
	return (0);
}

int	key_release(t_keys key, t_data *data)
{
	if (key == XK_s)
	{
		printf("release s\n");
		data->position.y = 0;
	}
	else if (key == XK_w)
	{
		printf("release w\n");
		data->position.y = 0;
	}
	else if (key == XK_a)
	{
		printf("release a\n");
		data->position.x = 0;
	}
	else if (key == XK_d)
	{
		printf("release d\n");
		data->position.x = 0;
	}
	// else if (key == XK_Left)
	//   printf("<-\n");
	// else if (key == XK_Right)
	//   printf("->\n");
	return (0);
}

void	update_movement(t_data *data)
{
	if (data->position.x == 1)
		data->position.screen_x += MV_SPEED;
	if (data->position.x == -1)
		data->position.screen_x -= MV_SPEED;
	if (data->position.y == 1)
		data->position.screen_y += MV_SPEED;
	if (data->position.y == -1)
		data->position.screen_y -= MV_SPEED;
	// if (data->position.y == -1)
	// 	data->position.screen_y -= 2;
	// if (data->position.y == -1)
	// 	data->position.screen_y -= 2;
}
