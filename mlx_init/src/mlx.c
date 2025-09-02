#include "../include/cub3d_mlx.h"
#include <stdio.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->adr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



