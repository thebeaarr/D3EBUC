#ifndef MLX_H
#define MLX_H
#include "../../cub3d_parser/include/parser.h"
#include "../../minilibx-linux/mlx.h"
typedef struct s_img 
{
  void *img ;
  char *adr ; 
  int		bits_per_pixel;
  int		line_length;
  int		endian;
}  t_image;

typedef struct s_data
{
  void *win ;
  void *mlx ;
  t_image *img;
  t_cub3d *cub3d;
}t_data;

void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void draw_2d(t_data *data);

#endif
