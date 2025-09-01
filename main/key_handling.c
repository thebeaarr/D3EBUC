#include "../mlx_init/include/cub3d_mlx.h"

int handle_close()
{
  printf("cub3D closed\n");
  exit(1);
}

int handle_key(int key , t_data *data)
{

  (void)data;

  if(key == 65307)
  {
    printf("cub3D closed(Esc)\n");
    exit(0);
  }
  else if (key == )
  return 0;
}