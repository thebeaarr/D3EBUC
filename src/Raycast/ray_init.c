/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:20:05 by sel-jari          #+#    #+#             */
/*   Updated: 2025/11/09 04:46:09 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	calculate_map_dimensions(t_data *data)
{
	int	y;

	y = 0;
	while (data->cub3d->map[y])
		y++;
	data->map_height = y;
}

void	dda_init(int x, t_ray *ray, t_data *data, t_player *player)
{
	calculate_map_dimensions(data);
	ray->camera_x = 2 * x / (float)data->win_width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
}
