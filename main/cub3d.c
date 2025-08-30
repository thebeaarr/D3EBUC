#include "../mlx_init/include/mlx.h"
#include "../cub3d_parser/include/parser.h"


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
    draw_2d(data);
  }
  else
    printf("ERROR:arguments\n");
  return 0;
}
