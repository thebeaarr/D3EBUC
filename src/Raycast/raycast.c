/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:19:56 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/11 17:19:57 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_single_ray(int x, t_ray *ray, t_data *data, t_player *player)
{
	int	temp;

	dda_init(x, ray, data, player);
	dda_inc(ray, player);
	temp = dda_algorithm(ray, data);
	calculate_wall_distance(ray, temp, data);
	draw_textured_wall(data, ray, x, temp);
}

void	raycast(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	data->win_height = 1000;
	data->win_width = 1000;
	while (x < data->win_width)
	{
		cast_single_ray(x, &ray, data, &data->player);
		x++;
	}
}
