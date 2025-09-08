#include "../mlx_init/include/cub3d_mlx.h"
#include <stdio.h>
#include <stdlib.h>

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
	int		byte;
	t_colors color;
	int		i;

	i = 0;
	data = (t_data *)arg;
	img = data->img;
	byte = img->bits_per_pixel / 8;
	for (int y = 0; y < 800; y++)
	{
		for (int x = 0; x < 800; x++)
		{
			i = 0;
			color = *(int *)(img->adr + x * byte + y * img->line_length);
			if (color == ORANGE)
			{
				my_mlx_pixel_put(data->img,x + data->position.x, y + data->position.y, color);
			}
			else
				my_mlx_pixel_put(data->img,x, y, color);
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
	printf("data lenght  : %d\n", data->img->line_length);
	printf("bit/pixel : %d\n",data->img->bits_per_pixel);
	draw_map_init(data);
	mlx_loop_hook(data->mlx, draw_map, data);
    // 4) Events + loop
    // mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_hook(data->win, 2, KeyPressMask, key_press, data);
	mlx_hook(data->win, 3, KeyReleaseMask, key_release, data);
    mlx_loop(data->mlx);
    return (0);
}
