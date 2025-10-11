#include "cub3d.h"

static void	draw_textured_wall(t_data *data, t_ray *ray, int x, int temp)
{
	int		y;
	t_colors		color;

	if (temp == 0) 
	{
		if (ray->dir.x > 0)
			color = RED;
		else
			color = GREEN;
	}
	else
	{
		if (ray->dir.y > 0)
			color = BLUE;
		else
			color = ORANGE;
	}

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(data->img, x, y, color);
		y++;
	}
	//s9ef
	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, x, y, GRAY);
		y++;
	}

	y = ray->draw_end;
	while (y < data->win_height)
	{
		my_mlx_pixel_put(data->img, x, y, 0x00404040); 
		y++;
	}
}

void	dda(int x, t_ray *ray, t_data *data, t_player *player)
{
	int	hit;
	
	ray->camera_x = 2 * x / (float)data->win_width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	
	// ray->deltadist.x = fabs(1.0 / ray->dir.x);
	// ray->deltadist.y = fabs(1.0 / ray->dir.y);
	ray->deltadist.x = sqrt(1.0 + ray->dir.y * ray->dir.y / (ray->dir.x * ray->dir.x));
	ray->deltadist.y = sqrt(1.0 + ray->dir.x * ray->dir.x / (ray->dir.y * ray->dir.y));	
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

	char **map = data->cub3d->map;
	int map_height = 37;
	int map_width = 28;

	int	temp;
	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			temp = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			temp = 1;
		}
		if (ray->map.y < 0 || ray->map.x < 0 || 
			ray->map.y >= map_height || ray->map.x >= map_width ||
			map[ray->map.y][ray->map.x] == '1')
			hit = 1;
	}
	if (temp)
		ray->wall_dist = (ray->sidedist.y - ray->deltadist.y);
	else
		ray->wall_dist = (ray->sidedist.x - ray->deltadist.x);

	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;

	if (ray->draw_start < 0)
		ray->draw_start = 0;

	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;

	if (temp == 0)
		ray->wall_x = player->pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = player->pos.x + ray->wall_dist * ray->dir.x;

	ray->wall_x -= floor(ray->wall_x);
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
		dda(x, &ray, data, &data->player);	
		x++;
	}
}