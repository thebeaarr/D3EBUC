/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:19:31 by sel-jari          #+#    #+#             */
/*   Updated: 2025/11/19 18:35:56 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	floor_and_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, x, y, data->cub3d->ceiling);
		y++;
	}
	y = ray->draw_end;
	while (y < data->win_height)
	{
		my_mlx_pixel_put(data->img, x, y, data->cub3d->floor);
		y++;
	}
}

unsigned int	get_pixel_color(t_texture *tex, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	pixel = tex->data.adr + (y * tex->data.line_length + x
			* (tex->data.bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

static t_texture	*select_texture(t_data *data, t_ray *ray, int side)
{
	t_texture	*tex;

	if (side == 0)
	{
		if (ray->dir.x > 0)
			tex = &data->texture[3];
		else
			tex = &data->texture[2];
	}
	else
	{
		if (ray->dir.y > 0)
			tex = &data->texture[1];
		else
			tex = &data->texture[0];
	}
	return (tex);
}

static void	draw_wall_column(t_data *data,
	t_ray *ray, t_texture *tex, int params[2])
{
	int				y;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_pixel_color(tex, params[1], tex_y);
		my_mlx_pixel_put(data->img, params[0], y, color);
		y++;
	}
}

void	draw_textured_wall(t_data *data, t_ray *ray, int x, int side)
{
	t_texture	*tex;
	double		wall_x;
	int			params[2];

	tex = select_texture(data, ray, side);
	wall_x = calculate_wall_x(data, ray, side);
	params[1] = calculate_tex_x(ray, tex, wall_x, side);
	params[0] = x;
	draw_wall_column(data, ray, tex, params);
	floor_and_ceiling(data, ray, x);
}
