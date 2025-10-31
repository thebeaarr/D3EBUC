/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 02:27:21 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/16 02:27:23 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*drawing vertical and horizontal lines (mmap frame)*/

static void	draw_frame_line(t_data *data, t_vector start, t_vector end)
{
	t_vector	offset;

	offset.x = start.x;
	while (offset.x < end.x)
	{
		offset.y = start.y;
		while (offset.y < end.y)
		{
			my_mlx_pixel_put(data->img, offset.x, offset.y, MAGENTA);
			offset.y++;
		}
		offset.x++;
	}
}

/* the background of the minimap, 
the colors will change most likely f textures,
try to remove this from draw_frame so u can see the difference. */

static void	draw_mmap_background(t_data *data)
{
	t_vector	offset;
	int			thickness;

	thickness = 3;
	offset.x = MINIMAP_X;
	while (offset.x < (data->win_width / 4) - thickness)
	{
		offset.y = MINIMAP_Y;
		while (offset.y < data->win_height - 13)
		{
			my_mlx_pixel_put(data->img, offset.x, offset.y, BLACK);
			offset.y++;
		}
		offset.x++;
	}
}

/* Just the map frame 
(calculation is a bit tricky but it shoudl work in diff dim)*/

void	draw_frame(t_data *data)
{
	int			thickness;
	t_vector	start;
	t_vector	end;

	thickness = 3;
	start.x = MINIMAP_X - thickness;
	start.y = MINIMAP_Y - thickness;
	end.x = data->win_width / 4;
	end.y = MINIMAP_Y;
	draw_frame_line(data, start, end);
	start.y = data->win_height - 10 - thickness;
	start.x = 10;
	end.y = data->win_height - 10;
	end.x = data->win_width / 4;
	draw_frame_line(data, start, end);
	start.x = MINIMAP_X - thickness;
	start.y = MINIMAP_Y;
	end.x = MINIMAP_X;
	end.y = data->win_height - 10;
	draw_frame_line(data, start, end);
	start.x = data->win_width / 4 - thickness;
	end.x = data->win_width / 4;
	end.y = data->win_height - 10;
	draw_frame_line(data, start, end);
	draw_mmap_background(data);
}
