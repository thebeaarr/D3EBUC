/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:40:27 by sel-jari          #+#    #+#             */
/*   Updated: 2025/09/18 00:40:29 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	gett_color(char c)
{
	if (c == '1')
		return (WHITE);
	if (c == '0')
		return (BLACK);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (ORANGE);
	return (GREEN);
}

void	get_player_pos(t_data *data)
{
	char		**map;
	int			i;
	int			j;

	map = data->cub3d->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (gett_color(map[i][j]) == ORANGE)
			{
				data->player.init_x = j;
				data->player.init_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
