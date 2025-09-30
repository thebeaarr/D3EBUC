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

int	is_border(t_data *data, int x, int y)
{
	return (data->img->adr[(y * data->img->line_length + x *
		(data->img->bits_per_pixel / 8))] == (char)BORDER);
}

static void	borders_stop(t_player *player, int x, int y)
{
	if (x == 0 && is_border(player->data, player->x + TILE - 1, player->y))
		player->action.screen_x -= MV_SPEED;
	if (x == 0 && is_border(player->data, player->x, player->y))
		player->action.screen_x += MV_SPEED;
	if (y == 0 && is_border(player->data, player->x, player->y + TILE - 1))
		player->action.screen_y -= MV_SPEED;
	if (y == 0 && is_border(player->data, player->x, player->y))
		player->action.screen_y += MV_SPEED;
}

static void	draw_map_init(void *arg)
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
}

int	draw_minimap(void *arg)
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
			player->x = player->init_x + x + (int)player->action.screen_x;
			player->y = player->init_y + y + (int)player->action.screen_y;
			borders_stop(player, x, y);
			my_mlx_pixel_put(data->img, player->x, player->y, ORANGE);
			x++;
		}
		y++;
	}
	player_view(&data->player);
	update_movement(player);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
