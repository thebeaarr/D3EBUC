/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:42:17 by sel-jari          #+#    #+#             */
/*   Updated: 2025/11/09 04:43:46 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_border(t_data *data, int x, int y, t_colors color)
{
	int		pixel_color;
	char	*pixel_addr;

	pixel_addr = data->img->adr
		+ (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	pixel_color = *(int *)pixel_addr;
	return (pixel_color == (int)color);
}

int	draw_tile(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
		{
			if ((x + j < ((data->win_width / 4) - 3) && x + j >= MINIMAP_X)
				&& (y + i) < (data->win_height - 13) && (y + i) >= MINIMAP_Y)
				my_mlx_pixel_put(data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
	return (0);
}

void	draw_map_init(t_data *data)
{
	char		**map;
	int			color;
	t_vector	index;
	t_vector_f	map_pos;

	map = data->cub3d->map;
	index.y = 0;
	while (map[index.y])
	{
		index.x = 0;
		while (map[index.y][index.x] && map[index.y][index.x] != '\n')
		{
			map_pos.x = ((float)index.x - data->player.pos.x) * TILE;
			map_pos.y = ((float)index.y - data->player.pos.y) * TILE;
			color = get_tile_color(map[index.y][index.x]);
			if (color == ORANGE)
				color = FLOOR;
			if (draw_tile(data, data->mmap.center.x + (int)map_pos.x,
					data->mmap.center.y + (int)map_pos.y, color))
				break ;
			index.x++;
		}
		index.y++;
	}
}

void	draw_player_mmap(t_data *data)
{
	t_vector	index;
	t_vector	p_pix;

	index.y = 0;
	while (index.y < TILE)
	{
		index.x = 0;
		while (index.x < TILE)
		{
			p_pix.x = data->mmap.center.x - TILE / 2 + index.x;
			p_pix.y = data->mmap.center.y - TILE / 2 + index.y;
			my_mlx_pixel_put(data->img, p_pix.x, p_pix.y, ORANGE);
			index.x++;
		}
		index.y++;
	}
}

void	minimap(t_data *data)
{
	init_minimap(data);
	draw_frame(data);
	draw_map_init(data);
	draw_player_mmap(data);
	player_view(&data->player);
}
