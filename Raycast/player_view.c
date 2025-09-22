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
		my_mlx_pixel_put(data->img, (int)(player->x - TILE / 2 + x) , (int)(player->y - TILE /2 + y) , GREEN);
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

	end_x = (int)(cosf(player->angle) * 60) + player->x - TILE / 2;
	end_y = (int)(sinf(player->angle) * 60) + player->y - TILE / 2;
	dx = end_x - player->x + TILE / 2;
	dy = end_y - player->y + TILE / 2;
	draw_line(player->data, player, dx, dy);
}
