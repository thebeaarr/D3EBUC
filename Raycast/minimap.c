/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:42:17 by sel-jari          #+#    #+#             */
/*   Updated: 2025/09/18 00:42:19 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_border(t_data *data, int x, int y)
{
	return (data->img->adr[(y * data->img->line_length + x *
		(data->img->bits_per_pixel / 8))] == (char)WHITE);
}

static void	borders_stop(t_data *data, int x, int y)
{
	t_player	*player;

	player = &data->player;
	if (x == 0 && is_border(data, player->x + 39, player->y))
		data->position.screen_x -= MV_SPEED;
	if (x == 0 && is_border(data, player->x, player->y))
		data->position.screen_x += MV_SPEED;
	if (y == 0 && is_border(data, player->x, player->y + 39))
		data->position.screen_y -= MV_SPEED;
	if (y == 0 && is_border(data, player->x, player->y))
		data->position.screen_y += MV_SPEED;
}

static int	draw_map_init(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
    char **map;

	map = data->cub3d->map;
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j] && map[i][j] != '\n'; j++)
        {
            int color = gett_color(map[i][j]);
			if (color == ORANGE)
				color = BLACK;
			for (int y = 0; y < TILE; y++)
			{
				for (int x = 0; x < TILE; x++)
					my_mlx_pixel_put(data->img,j * TILE + x,i * TILE + y,color);
			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

int	draw_map(void *arg)
{
	t_data 		*data;
	t_player	*player;
	int			x;
	int			y;

	data = (t_data *)arg;
	player	= &data->player;
	y = 0;
	draw_map_init(data);
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			player->x = player->init_x * TILE + x + (int)data->position.screen_x;
			player->y = player->init_y * TILE + y + (int)data->position.screen_y;
			borders_stop(data, x, y);
			my_mlx_pixel_put(data->img, player->x, player->y, ORANGE);
			x++;
		}
		y++;
	}
	update_movement(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
