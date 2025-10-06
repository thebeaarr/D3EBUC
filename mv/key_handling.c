/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:42:12 by sel-jari          #+#    #+#             */
/*   Updated: 2025/09/18 00:42:26 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(t_keys key, t_player *player)
{
	if (key == XK_escape)
		handle_close();	
	player_pos(player, key);
	player_rot(player, key);
	return (0);
}

int	key_release(t_keys key, t_player *player)
{
	if (key == XK_s)
		player->action.down = 0;
	else if (key == XK_w)
		player->action.up = 0;
	else if (key == XK_a)
		player->action.left = 0;
	else if (key == XK_d)
		player->action.right = 0;
	else if (key == XK_Left)
		player->action.rot_left = 0;
	else if (key == XK_Right)
		player->action.rot_right = 0;
	return (0);
}

/*hadi new approach so i can perform the dda , u can checkout other branches to see the difference*/
void	update_movement(t_player *player)
{
	update_pos(player);	
	update_rot(player);
}