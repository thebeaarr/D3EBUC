#include "../cub3d_parser/include/parser.h"


int main(int ac , char **av)
{
  if(ac == 2)
  {
    t_cub3d *cub3d = main_parser(av[1]);
    (void)cub3d;
  }
  else
    printf("ERROR:arguments\n");
  return 0;
}
