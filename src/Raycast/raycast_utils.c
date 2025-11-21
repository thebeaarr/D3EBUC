/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:20:05 by sel-jari          #+#    #+#             */
/*   Updated: 2025/11/09 04:46:09 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	dda_inc(t_ray *ray, t_player *player)
{
	ray->deltadist.x = fabs(1.0 / ray->dir.x);
	ray->deltadist.y = fabs(1.0 / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (player->pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - player->pos.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (player->pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - player->pos.y) * ray->deltadist.y;
	}
}

int	dda_algorithm(t_ray *ray, t_data *data)
{
	int	wall;
	int	temp;

	wall = 0;
	while (!wall)
	{
		if (ray->sidedist.y < ray->sidedist.x)
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			temp = 1;
		}
		else
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			temp = 0;
		}
		if (ray->map.y < 0 || ray->map.x < 0
			|| data->cub3d->map[ray->map.y][ray->map.x] == '1')
			wall = 1;
	}
	return (temp);
}

void	calculate_wall_distance(t_ray *ray, int temp, t_data *data)
{
	if (temp)
		ray->wall_dist = (ray->sidedist.y - ray->deltadist.y);
	else
		ray->wall_dist = (ray->sidedist.x - ray->deltadist.x);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = (data->win_height / 2) - (ray->line_height / 2);
	ray->draw_end = (data->win_height / 2) + (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (temp == 0)
		ray->wall_x = data->player.pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = data->player.pos.x + ray->wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}
