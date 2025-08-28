#include "../cub3d_parser/include/parser.h"


int main(int ac , char **av)
{
  if(ac == 2)
  {
    t_cub3d *cub3d = main_parser(av[1]);
     if(cub3d != NULL)
    {
    //   char **map = cub3d->map;
    //   for (int i = 0; map[i]; i++)
    //   {
    //     for (int j = 0; map[i][j]; j++)
    //     {
    //       printf("%c", map[i][j]);
    //     }
    //   }
    //   for (int i = 0; cub3d->textures[i]; i++)
    //   {
    //     for (int j = 0; cub3d->textures[i][j]; j++)
    //       printf("%s", cub3d->textures[i][j]);
    //   }
    //   printf("f = %d, c = %d", cub3d->colors[0], cub3d->colors[1]);
    }
    printf("F = %d, C = %d", cub3d->colors[0],     cub3d->colors[1]);
  }
  else
    printf("ERROR:arguments\n");
  return 0;
}