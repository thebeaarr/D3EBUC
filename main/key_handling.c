#include "../mlx_init/include/cub3d_mlx.h"
#include <math.h>

int handle_close()
{
  printf("cub3D closed\n");
  exit(1);
}
static int gett_color(char c)
{
    if (c == '1')
		return WHITE;
    if (c == '0')
		return BLACK;
    if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return ORANGE;
    return BLACK;
}
int key_press(t_keys key , t_data *data)
{
    if(key == 65307)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
	{
		data->movement.down = 1;
	}
	else if (key == XK_w)
	{
		data->movement.up = 1;
	}
    else if (key == XK_a)
	{
		data->movement.left = 1;
	}
    else if (key == XK_d)
	{
		data->movement.right = 1;
	}
    else if (key == XK_Left)
	{
		data->movement.rot_left = 1;
	}
    else if (key == XK_Right)
	{
		data->movement.rot_right = 1;
	}
    return 0;
}

int key_release(t_keys key , t_data *data)
{
    if(key == 65307)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
	{
		data->movement.down = 0;
	}
	else if (key == XK_w)
	{
		data->movement.up = 0;
	}
    else if (key == XK_a)
	{
		data->movement.left = 0;
	}
    else if (key == XK_d)
	{
		data->movement.right = 0;
	}
    else if (key == XK_Left)
	{
		data->movement.rot_left = 0;
	}
    else if (key == XK_Right)
	{
		data->movement.rot_right = 0;
	}
    return 0;
}

void	update_movement(t_data *data)
{
	float speed = data->movement.speed;
	float rot_speed = 0.05;
	
	if (data->movement.up)
		data->position.y -= speed;
	if (data->movement.down)
		data->position.y += speed;
	if (data->movement.left)
		data->position.x -= speed;
	if (data->movement.right)
		data->position.x += speed;
	if (data->movement.rot_left)
		data->angle -= rot_speed;
	if (data->movement.rot_right)
		data->angle += rot_speed;
}

int	draw_map_init(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
    char **map = data->cub3d->map;
    int tile = 40;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            int color = gett_color(map[i][j]);
			for (int y = 0; y < tile; y++)
			{
				for (int x = 0; x < tile; x++)
				my_mlx_pixel_put(data->img,j * tile + x,i * tile + y,color);
			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

int	draw_map(void *arg)
{
	t_data *data;
	char **map;
	int tile = 40;
	int screen_x;
	int screen_y;
	int color;
	int x;
	int y;
	int i;
	int j;
	data = (t_data *)arg;
	map = data->cub3d->map;
	
	for (int y = 0; y < 800; y++)
	{
		for (int x = 0; x < 800; x++)
		{
			my_mlx_pixel_put(data->img, x, y, BLACK);
		}
	}
	
	for (i = 0; map[i]; i++)
	{
		for (j = 0; map[i][j]; j++)
		{
			color = gett_color(map[i][j]);
			
			if (map[i][j] != 'N' && map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != 'S')
			{
				for (y = 0; y < tile; y++)
				{
					for (x = 0; x < tile; x++)
					{
						screen_x = j * tile + x;
						screen_y = i * tile + y;
						
						if (screen_x >= 0 && screen_x < 800 && screen_y >= 0 && screen_y < 800)
							my_mlx_pixel_put(data->img, screen_x, screen_y, color);
					}
				}
			}
		}
	}
	for (i = 0; map[i]; i++)
	{
		for (j = 0; map[i][j]; j++)
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
			{
				
				color = ORANGE;
				for (y = 0; y < tile; y++)
				{
					for (x = 0; x < tile; x++)
					{
						screen_x = j * tile + x + (int)data->position.x;
						screen_y = i * tile + y + (int)data->position.y;
						
						if (screen_x >= 0 && screen_x < 800 && screen_y >= 0 && screen_y < 800)
							my_mlx_pixel_put(data->img, screen_x, screen_y, color);
					}
				}
			}
		}
	}
	draw_direction_line(data);
	
	update_movement(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	draw_direction_line(t_data *data)
{
	int		start_x, start_y, end_x, end_y;
	int		tile = 40;
	float	line_length = 30.0;
	
	start_x = data->position.x * tile + tile / 2;
	start_y = data->position.y * tile + tile / 2;
	end_x = start_x + (int)(cosf(data->angle) * line_length);
	end_y = start_y + (int)(sinf(data->angle) * line_length);
	
	draw_line(data, start_x, start_y, end_x, end_y, GREEN);
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;
	
	dx = x1 - x0;
	dy = y1 - y0;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	if (steps == 0)
	{
		if (x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 800)
			my_mlx_pixel_put(data->img, x0, y0, color);
		return;
	}
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;
	x = (float)x0;
	y = (float)y0;
	i = 0;
	while (i <= steps)
	{
		if (x >= 0 && x < 800 && y >= 0 && y < 800)
			my_mlx_pixel_put(data->img, x, y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}