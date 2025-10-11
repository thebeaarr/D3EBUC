#include "cub3d.h"

void	draw_line(t_data *data, t_player *player , int dx, int dy)
{
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int	steps;
	int	i;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = (float)dx / (float)steps;	
	y_inc = (float)dy / (float)steps;	
	i = 0;	
	x = 0;
	y = 0;
	while (i < steps)
	{
		if (is_border(player->data, (int)(((player->pos.x - 0.5) * TILE) + CENTER + x), 700 + (int)(((player->pos.y - 0.5) * TILE) + CENTER + y)))
			break;			
		my_mlx_pixel_put(data->img, (int)(((player->pos.x - 0.5) * TILE) + CENTER + x) , 700 + (int)(((player->pos.y - 0.5) * TILE) + CENTER + y) , RED);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	player_view(t_player *player)
{

	int	end_x;
	int	end_y;
	int	dx;
	int	dy;
	// float	next_ray;
	// int	i = 0;
	// int		raysnum;

	// raysnum = 100;
	// next_ray = M_PI_2 / (float)raysnum;
	// while(i < raysnum)
	// {
	// 	end_x = (int)(cos(-M_PI_4 + player->angle + next_ray * i) * RAYSIZE) + player->x - TILE / 2;
	// 	end_y = (int)(sin(- M_PI_4 + player->angle + next_ray * i) * RAYSIZE) + player->y - TILE / 2;
	// 	dx = end_x - player->x + TILE / 2;
	// 	dy = end_y - player->y + TILE / 2;
	// 	draw_line(player->data, player, dx, dy);
	// 	i++;
	// }
	// end_x = (int)(cos(player->angle) * RAYSIZE) + ((player->pos.y - 0 .5) * TILE) + CENTER;
	// end_y = (int)(sin(player->angle ) * RAYSIZE) + ((player->pos.y - 0 .5) * TILE) + CENTER;

	end_x = player->dir.x * RAYSIZE;
	end_y = player->dir.y * RAYSIZE;
	dx = end_x;
	dy = end_y;
	// printf("%d %d\n",end_x, end_y);
	draw_line(player->data, player, dx, dy);
}