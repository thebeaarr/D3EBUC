#include "../mlx_init/include/cub3d_mlx.h"
#include <stdio.h>
#include <stdlib.h>

// int handle_close()
// {
//   printf("tfi daw\n");
//   exit(1);
// }

// int handle_key(int a  , t_data *data)
// {
//   // something like 
//   (void)data;
//     printf("keysym is %d , %c \n",a , a);

//   return 0;
// }

/* render_init.c */
// int init_mlx(t_data *data)
// {
//     data->mlx = mlx_init();
//     if (!data->mlx)
//         return (0);

//     data->win = mlx_new_window(data->mlx, 1000, 800, "Cub3D");
//     if (!data->win)
//         return (0);

//     data->img = malloc(sizeof(t_image));
//     if (!data->img)
//         return (0);

// 	data->img->img = mlx_new_image(data->mlx, 1000, 800);
//     data->img->adr = mlx_get_data_addr(data->img->img,
//         &data->img->bits_per_pixel,
//         &data->img->line_length,
//         &data->img->endian);
//     return (1);
// }

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
    int tile = 60;

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
	t_image *img;
    int tile = 60;

	data = (t_data *)arg;
	img = data->img;
	for (int j = 0; img->adr[j]; j++)
	{
		int color = gett_color(img->adr[j]);
		if (color == ORANGE)
		{
			for (int y = 0; y < tile; y++)
			{
				for (int x = 0; x < tile; x++)
				my_mlx_pixel_put(data->img,j * tile + x + data->position.x * 5,(j * img->line_length) * tile + y + data->position.y ,color);
			}
		}
		else
			for (int y = 0; y < tile; y++)
			{
				for (int x = 0; x < tile; x++)
				my_mlx_pixel_put(data->img,j * tile + x,j * img->line_length * tile + y,color);
			}
	}
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
int main(int ac, char **av)
{
    t_data *data;

    if (ac != 2)
    {
        printf("ERROR: arguments\n");
        return (1);
    }

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);

    // 1) Parse map (a problem in the parsing still checking for it)
    data->cub3d = get_file_as_struct(av[1]);
    if (!data->cub3d)
    {
        printf("ERROR: parsing\n");
        free(data);
        return (1);
    }
    // print_cub3d(data->cub3d);

    // 2) Initialize MLX
    if (!init_mlx(data))
    {
        printf("ERROR: mlx init\n");
		// freeadd_exit(); later
        free(data->cub3d);
        free(data);
        return (1);
    }
	data->position.x = 0;
	data->position.y = 0;
    // 3) Draw the map (2D debug)
	draw_map_init(data);
	mlx_loop_hook(data->mlx, draw_map, data);
    // 4) Events + loop
    mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_hook(data->win, 2, KeyPressMask, key_press, data);
	mlx_hook(data->win, 3, KeyReleaseMask, key_release, data);
    mlx_loop(data->mlx);
    return (0);
}
