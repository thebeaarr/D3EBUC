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
	return (data->img->adr[(y * data->img->line_length + x
				* (data->img->bits_per_pixel / 8))] == (char)BORDER);
}

void	draw_tile(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
		{
			my_mlx_pixel_put(data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_map_init(void *arg)
{
	t_data	*data;
	char	**map;
	int		y;
	int		x;
	int		color;

	data = (t_data *)arg;
	map = data->cub3d->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			color = get_tile_color(map[y][x]);
			if (color == ORANGE)
				color = BLACK;
			draw_tile(data, x * TILE, 700 + (y * TILE), color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

void	draw_player(t_data *data, t_player *player)
{
	t_vector	index;
	t_vector	p_pix;
	t_vector	map;

	map.x = (player->pos.x - 0.5) * TILE;
	map.y = (player->pos.y - 0.5) * TILE;
	index.y = 0;
	while (index.y < TILE)
	{
		index.x = 0;
		while (index.x < TILE)
		{
			p_pix.x = (int)map.x + index.x;
			p_pix.y = (int)map.y + index.y;
			my_mlx_pixel_put(data->img, p_pix.x, 700 + p_pix.y, ORANGE);
			index.x++;
		}
		index.y++;
	}
}

int	draw_minimap(void *arg)
{
	t_data		*data;
	t_player	*player;

	data = (t_data *)arg;
	player = &data->player;
	raycast(data);
	draw_map_init(data);
	draw_player(data, player);
	player_view(player);
	update_transform(player);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	usleep(100);
	return (0);
}
