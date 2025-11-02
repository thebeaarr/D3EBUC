/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:19:31 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/31 14:59:27 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	floor_and_scealing(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, x, y, GRAY);
		y++;
	}
	y = ray->draw_end;
	while (y < data->win_height)
	{
		my_mlx_pixel_put(data->img, x, y, 0x00404040);
		y++;
	}
}

void	draw_textured_wall(t_data *data, t_ray *ray, int x, int temp)
{
	int				y;
	t_colors		color;

	if (temp == 0)
	{
		if (ray->dir.x > 0)
			color = RED;
		else
			color = GREEN;
	}
	else
	{
		if (ray->dir.y > 0)
			color = BLUE;
		else
			color = ORANGE;
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(data->img, x, y, color);
		y++;
	}
	floor_and_scealing(data, ray, x);
}
