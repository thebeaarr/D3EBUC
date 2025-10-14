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

int	is_border(t_data *data, int x, int y, t_colors color)
{
	int		pixel_color;
	char	*pixel_addr;

	pixel_addr = data->img->adr
		+ (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	pixel_color = *(int *)pixel_addr; // read all 4 bytes

	return (pixel_color == (int)color);
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
			if (is_border(data, x + j, y + i, MAGENTA))
				break;
			my_mlx_pixel_put(data->img, x + j, y + i, color);
			j++;
		}
		// if (is_border(data, x + j, y +i,  MAGENTA))
		// 	break;
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
	t_vector new;

	data = (t_data *)arg;
	map = data->cub3d->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			new.x = (data->player.pos.x - data->init_pos.x) * TILE;
			new.y = (data->player.pos.y - data->init_pos.y) * TILE;
			color = get_tile_color(map[y][x]);
			if (color == ORANGE)
				color = BLACK;
			draw_tile(data, MINIMAP_X + x  * TILE - new.x,  MINIMAP_Y + y * TILE - new.y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data, t_player *player)
{
	t_vector	index;
	t_vector	p_pix;
	t_vector	map;

	(void)player;
	map.x = (data->init_pos.x - 0.5) * TILE;
	map.y = (data->init_pos.y - 0.5) * TILE;
	index.y = 0;
	while (index.y < TILE)
	{
		index.x = 0;
		while (index.x < TILE)
		{
			p_pix.x = (int)map.x + index.x;
			p_pix.y = (int)map.y + index.y;
			my_mlx_pixel_put(data->img, MINIMAP_X + p_pix.x, MINIMAP_Y + p_pix.y, ORANGE);
			index.x++;
		}
		index.y++;
	}
}

void	draw_cadre(t_data * data)
{
	int	x;
	int	y;

	y = 800;
	while (y < 803)
	{
		x = 10;
		while (x < data->win_width / 4)
		{
			my_mlx_pixel_put(data->img, x, y, MAGENTA);
			x++;
		}
		y++;
	}
	y = data->win_width - 13;
	while (y < data->win_width - 10)
	{
		x = 10;
		while (x < data->win_width / 4)
		{
			my_mlx_pixel_put(data->img, x, y, MAGENTA);
			x++;
		}
		y++;
	}

	while (x < (data->win_width / 4) + 3)
	{
		y = 800;
		while (y < data->win_height - 10)
		{
			my_mlx_pixel_put(data->img, x, y, MAGENTA);
			y++;
		}
		x++;
	}

	x = 10; 	
	while (x < 13)
	{
		y = 800;
		while (y < data->win_height - 10)
		{
			my_mlx_pixel_put(data->img, x, y, MAGENTA);
			y++;
		}
		x++;
	}
}

int	draw_minimap(void *arg)
{
	t_data		*data;
	t_player	*player;

	data = (t_data *)arg;
	player = &data->player;
	raycast(data);
	draw_cadre(data);
	draw_map_init(data);
	draw_player(data, player);
	player_view(player);
	update_transform(player);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	usleep(100);
	return (0);
}
