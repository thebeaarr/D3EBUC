#include "../mlx_init/include/cub3d_mlx.h"
#include <stdio.h>
#include <stdlib.h>
int handle_close()
{
  printf("tfi daw\n");
  exit(1);
}

int handle_key(int a  , t_data *data)
{
  printf("-------------------------------------------------------------content------------------------------------------------------\n");
  print_cub3d(data->cub3d);
  printf("-------------------------------------------------------------content------------------------------------------------------\n");

  if(a == 65307)
  {
    printf("good bye!");
    exit(0);
  }
  return 0;
}
int init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return (0);

    data->win = mlx_new_window(data->mlx, 1000, 500, "medlkhdr");
    if (!data->win)
        return (0);

    data->img = malloc(sizeof(t_image));
    if (!data->img)
        return (0);

    data->img->img = mlx_new_image(data->mlx, 1000, 500);
    data->img->adr = mlx_get_data_addr(data->img->img,
        &data->img->bits_per_pixel,
        &data->img->line_length,
        &data->img->endian);
    return (1);
}
static int get_color_(char c)
{
    if (c == '1') return 0xFFFFFF; // wall
    if (c == '0') return 0x000000; // empty
    if (c == 'P') return 0xFF0000; // player
    return 0x7F7F7F;               // unknown
}

void draw_map(t_data *data)
{
    char **map = data->cub3d->map;
    int tile = 20;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            int color = get_color_(map[i][j]);
            for (int y = 0; y < tile; y++)
            {
                for (int x = 0; x < tile; x++)
                {
                    my_mlx_pixel_put(data->img,
                        j * tile + x,
                        i * tile + y,
                        color);
                }
            }
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
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

    // 1) Parse map
    data->cub3d = main_parser(av[1]);
    if (!data->cub3d)
    {
        printf("ERROR: parsing\n");
        free(data);
        return (1);
    }
    print_cub3d(data->cub3d);

    // 2) Initialize MLX
    if (!init_mlx(data))
    {
        printf("ERROR: mlx init\n");
        free(data->cub3d);
        free(data);
        return (1);
    }

    // 3) Draw the map (2D debug)
    draw_map(data);

    // 4) Events + loop
    mlx_hook(data->win, 17, 0, handle_close, data);
    mlx_key_hook(data->win, handle_key, data);
    mlx_loop(data->mlx);

    return (0);
}
