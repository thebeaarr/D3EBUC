#include "../mlx_init/include/cub3d_mlx.h"

int handle_close()
{
  printf("cub3D closed\n");
  exit(1);
}

int key_press(t_keys key , t_data *data)
{
    (void)data;
    if(key == 65307)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
	{
		data->position.y += +1;
    	printf("s\n");
	}
	else if (key == XK_w)
	{

		data->position.y -= 1;
		printf("w\n");
	}
    else if (key == XK_a)
	{

		data->position.x -= 1;
		printf("a\n");
	}
    else if (key == XK_d)
	{
		data->position.x += 1;
		printf("d\n");
	}
    else if (key == XK_Left)
	{

      printf("<-\n");
	}
    else if (key == XK_Right)
	{

      printf("->\n");
	}
    return 0;
}

int key_release(t_keys key , t_data *data)
{
    (void)data;
    if(key == XK_escape)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
	{
		printf("release s\n");
		data->position.y = 0;
	}
	else if (key == XK_w)
	{
		printf("release s\n");
		data->position.y = 0;
	}
    else if (key == XK_a)
	{
		printf("release s\n");
		data->position.x = 0;
	}
    else if (key == XK_d)
	{
		printf("release s\n");
		data->position.x = 0;
	}
    // else if (key == XK_Left)
    //   printf("<-\n");
    // else if (key == XK_Right)
    //   printf("->\n");
     return 0;
}

static int gett_color(char c)
{
    if (c == '1')
		return WHITE;
    if (c == '0')
		return BLACK;
    if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return ORANGE;
    return GREEN;
}

int	draw_map_init(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
    char **map = data->cub3d->map;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j] && map[i][j] != '\n'; j++)
        {
            int color = gett_color(map[i][j]);
			if (color == ORANGE)
				color = BLACK;
			for (int y = 0; y < TILE; y++)
			{
				for (int x = 0; x < TILE; x++)
				{
					my_mlx_pixel_put(data->img,j * TILE + x,i * TILE + y,color);
				}
			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

void	update_movement(t_data *data)
{

	if (data->position.x)
		data->position.screen_x += MV_SPEED;
	if (data->position.y == 1)
		data->position.screen_y += MV_SPEED;
	if (data->position.x == -1)
		data->position.screen_x -= MV_SPEED;
	if (data->position.y == -1)
		data->position.screen_y -= MV_SPEED;
	// if (data->position.y == -1)
	// 	data->position.screen_y -= 2;
	// if (data->position.y == -1)
	// 	data->position.screen_y -= 2;
}

void	borders_stop(t_data *data, int x, int y)
{
	t_player	*player;

	player = &data->player;
	if (x == 0 && data->img->adr[(player->y * data->img->line_length + (player->x + 39) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_x -= MV_SPEED;
	if (x == 0 && data->img->adr[(player->y * data->img->line_length + (player->x) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_x += MV_SPEED;
	if (y == 0 && data->img->adr[((player->y + 39) * data->img->line_length + (player->x) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_y -= MV_SPEED;
	if (y == 0 && data->img->adr[((player->y)* data->img->line_length + (player->x) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_y += MV_SPEED;
}

int	draw_map(void *arg)
{

	t_data 		*data;
	t_player	*player;
	char		**map;

	data = (t_data *)arg;
	player	= &data->player;
    map = data->cub3d->map;
	draw_map_init(data);
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j] && map[i][j] != '\n'; j++)
        {
            int color = gett_color(map[i][j]);
			
			for (int y = 0; color == ORANGE && y < TILE; y++)
			{
				for (int x = 0; x < TILE; x++)
				{
					player->x = j * TILE + x + (int)data->position.screen_x;
					player->y = i * TILE + y + (int)data->position.screen_y;
					// borders_stop(data, x ,y);
					my_mlx_pixel_put(data->img, player->x , player->y, color);
				}
			}
        }
    }
	update_movement(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}