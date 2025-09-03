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
    if(key == 65307)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }

    else if (key == XK_s)
	{
		// data->position.y = 0;
    	printf("relase s\n");
	}
	else if (key == XK_w)
	{

		// data->position.y = 0;
		printf("relase w\n");
	}
    else if (key == XK_a)
	{

		// data->position.x = 0;
		printf("relase a\n");
	}
    else if (key == XK_d)
	{
		// data->position.x = 0;
		printf("relase d\n");
	}
    else if (key == XK_Left)
	{

      printf("<-\n");
	}
    else if (key == XK_Right)
	{

      printf("->\n");
	}
    // else if (key == XK_s)
    //   printf("relase s\n");
    // else if (key == XK_a)
    //   printf("release a\n");
    // else if (key == XK_d)
    //   printf("release d\n");
    // else if (key == XK_w)
    //   printf("release w\n");
    // else if (key == XK_Left)
    //   printf("release <-\n");
    // else if (key == XK_Right)
    //   printf("release ->\n");
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
    int tile = 40;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j] && map[i][j] != '\n'; j++)
        {
            int color = gett_color(map[i][j]);
			if (color == ORANGE)
				color = BLACK;
			for (int y = 0; y < tile; y++)
			{
				for (int x = 0; x < tile; x++)
				{
					my_mlx_pixel_put(data->img,j * tile + x,i * tile + y,color);
				}
			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

int	draw_map(void *arg)
{

	t_data *data;

	data = (t_data *)arg;
    char **map = data->cub3d->map;
    int tile = 40;
	draw_map_init(data);
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            int color = gett_color(map[i][j]);
			for (int y = 1; y < tile && color == ORANGE; y++)
			{
				for (int x = 1; x < tile; x++)
					my_mlx_pixel_put(data->img,j * tile + x + data->position.x * 20, i * tile + y + data->position.y * 20, color);

			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}