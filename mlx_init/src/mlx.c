#include "../include/cub3d_mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../cub3d_parser/include/parser.h"
#include "../../minilibx-linux/mlx.h"
void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool chef_raycaster(t_cub3d *cub3d)
{
	t_data *_config;
	printf("seg here \n");  
	_config = malloc(sizeof(t_data));
	_config->cub3d = cub3d ;
	printf("seg here \n");  
	_config->mlx  = mlx_init();
	_config->win =  mlx_new_window(_config->mlx  , 500 , 300 , "test");
	_config->img = malloc(sizeof(t_image));
	_config->img->img = mlx_new_image(_config->mlx, 500 , 300);
	_config->img->adr = mlx_get_data_addr(_config->img->img  ,&_config->img->bits_per_pixel, &_config->img->line_length , &_config->img->endian );
	printf("--%x --- %d--- %d---\n", ++*_config->img->adr++ , _config->img->line_length ,_config->img->endian);
	// u trying to tell me that the adr is nothign ??  is a space then okay 
	/// that's toought
	// for(int i = 0 ;_config->img->adr ; i++)
	// 	printf("%c\n" , _config->img->adr[i]);
	// that's not good hhhhhh 
	// anyway try to crazy hhh
	for(int i  = 10 ; i < 500 ; i++)
	{
		for(int j = 10 ; j< 300 ; j++)
			my_mlx_pixel_put(_config->img ,i ,j , i * 255 - j * 255);	
	}
	mlx_put_image_to_window(_config->mlx , _config->win , _config->img->img , 0, 0);
	while(1); // mn b3d w nchufo hadchi kifach khdam
	return true;
}

