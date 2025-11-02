/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 01:06:53 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/17 01:06:58 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	raycast(data);
	minimap(data);
	update_transform(&data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	usleep(100);
	return (0);
}
