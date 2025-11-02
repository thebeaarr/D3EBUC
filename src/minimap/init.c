/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 03:57:40 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/16 03:57:41 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap(t_data *data)
{
	data->mmap.center.x = MINIMAP_X + ((data->win_width / 4) - MINIMAP_X) / 2;
	data->mmap.center.y = MINIMAP_Y + ((data->win_height - 10) - MINIMAP_Y) / 2;
}
