/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:35:13 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/19 18:43:48 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double	calculate_wall_x(t_data *data, t_ray *ray, int side)
{
	double	wall_x;

	if (side == 0)
		wall_x = data->player.pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = data->player.pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calculate_tex_x(t_ray *ray, t_texture *tex, double wall_x, int side)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)(tex->width));
	if ((side == 0 && ray->dir.x > 0) || (side == 1 && ray->dir.y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
