#include "../cub3d_parser/include/parser.h"


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

int main(int ac , char **av)
{
  if(ac == 2)
  {
    t_cub3d *cub3d = main_parser(av[1]);
    print_cub3d(cub3d);
    // initialize the mlx ? // initialize( )
    // t_data { cub3d  , mlx min img , textures } ...
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 1000, 500, "medlkhdr");
    mlx_hook(win , 17 , 0 ,handle_close ,NULL );
    mlx_key_hook(win , handle_key , NULL);
    mlx_loop(mlx);
  }
  else
    printf("ERROR:arguments\n");
  return 0;
}
