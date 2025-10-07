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

// static void	borders_stop(t_player *player, t_vector index, t_vector p_pix)
// {
// 	if (index.x == 0 && is_border(player->data, p_pix.x + TILE - 1, p_pix.y))
// 		player->pos.x -= 0.01;
// 	if (index.x == 0 && is_border(player->data, p_pix.x, p_pix.y))
// 		player->pos.x += 0.01;
// 	if (index.y == 0 && is_border(player->data, p_pix.x, p_pix.y + TILE - 1))
// 		player->pos.y -= 0.01;
// 	if (index.y == 0 && is_border(player->data, p_pix.x, p_pix.y))
// 		player->pos.y += 0.01;
// }

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
	t_vector	index;
	t_vector	p_pix;
	t_vector	map;

	data = (t_data *)arg;
	player	= &data->player;
	map.x = (player->pos.x - 0.5) * TILE;
	map.y = (player->pos.y - 0.5) * TILE;
	index.y = 0;
	draw_map_init(data);
	while (index.y < TILE)
	{
		index.x = 0;
		while (index.x < TILE)
		{
			p_pix.x = (int)map.x + index.x;
			p_pix.y = (int)map.y + index.y;
			// borders_stop(player, index, p_pix);
			my_mlx_pixel_put(data->img, p_pix.x, p_pix.y, ORANGE);
			index.x++;
		}
		index.y++;
	}
	player_view(&data->player);
	update_movement(player);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	usleep(100);
	return (0);
}
