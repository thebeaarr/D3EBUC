#include "../include/mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int handle_close()
{
  printf("tfi daw\n");
  exit(1);
}

int handle_key(int a )
{
  if(a == 65307)
  {
    printf("good bye!");
    exit(0);
  }
  return 0;
}

void draw_2d(t_data *data)
{
  data->mlx  = mlx_init();
  data->win  = mlx_new_window(data->mlx, 1000, 500, "medlkhdr");
  mlx_hook(data->win , 17 , 0 ,handle_close ,NULL );
  mlx_key_hook(data->win , handle_key , NULL);
  mlx_loop(data->mlx);
}
