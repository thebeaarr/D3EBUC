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

int main(int ac , char **av)
{
  if(ac == 2)
  {
    t_data *data;
    data = malloc(sizeof(t_data));
    t_cub3d *cub3d = main_parser(av[1]);
    data->cub3d = cub3d;
    print_cub3d(cub3d);
    // initialize the mlx ? // initialize()
    // t_data { cub3d  , mlx min img , textures } ...
    // draw_2d(data);
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 1000, 500, "medlkhdr");
    
    // Initialize the image
    data->img = malloc(sizeof(t_image));
    data->img->img = mlx_new_image(data->mlx, 1000, 500);
    data->img->adr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, 
                                       &data->img->line_length, &data->img->endian);
    mlx_hook(data->win, 17, 0, handle_close, NULL);
    mlx_key_hook(data->win, handle_key, data);
    for(int i =  0 ; i < 1000 ; i++)
    {
      for(int j = 0 ; j  < 500 ; j++)
      {
        // draw 2d game i guess .... ( i forgot how to put pixel on image hahahha) 
      }
    }
    mlx_loop(data->mlx);
  }
  else
    printf("ERROR:arguments\n");
  return 0;
}
