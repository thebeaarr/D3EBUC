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
int color_render(char c)
{
	if(c == '1')
        return 0x00FF00;   // green
	if(c == ' ')
        return 0x000000;   // black
	return 0x0000FF;   // blue
}

void draw_shit(t_data *_config)
{
	char **map = _config->cub3d->map;
	for(int i = 0 ; map[i] ; i++)
	{
		for(int j = 0 ; map[i][j]; j++)
		{
			for(int x = 0 ; x  < _config->cub3d->tile; x ++)
			{
				for(int  y = 0; y < _config->cub3d->tile ; y++)
					my_mlx_pixel_put(_config->img, x + j * _config->cub3d->tile , y + i * _config->cub3d->tile , color_render(map[i][j]));
			}
		}
	}
	for(int i = -3 ; i < 3 ; i++)
	{
		for(int j = -3 ; j < 3 ; j++)
			my_mlx_pixel_put(_config->img ,_config->cub3d->player_x + i, _config->cub3d->player_y + j, 0x00FFFF);
	}
}

bool is_key_mover2(int keycode)
{
	return keycode == 119 || keycode == 115 || keycode == 100 || keycode == 97;
}
void move_player2(int keycode , t_data *config)
{
	if(keycode == 119)
	{
		char **map = config->cub3d->map ;
		if( map[(config->cub3d->player_y  - 3 ) / config->cub3d->tile][(config->cub3d->player_x) / config->cub3d->tile] == '1')
		{
			printf("walls in front of you\n");
			return ;
		}
		config->cub3d->player_y -= 3;
		printf("↑\n");
	}
	else if(keycode ==115)
	{
		char **map = config->cub3d->map ;
		if( map[(config->cub3d->player_y  + 3) / config->cub3d->tile][(config->cub3d->player_x) / config->cub3d->tile] == '1')
		{
			printf("walls in front of you\n");
			return ;
		}
		printf("↓\n");
		config->cub3d->player_y+= 3;
	}
	else if(keycode == 100)
	{
		char **map = config->cub3d->map ;
		if( map[(config->cub3d->player_y) / config->cub3d->tile][(config->cub3d->player_x + 3) / config->cub3d->tile] == '1')
		{
			printf("walls in front of you\n");
			return ;
		}
		printf("→\n");
		config->cub3d->player_x+= 3;
	}
	else if(keycode == 97)
	{
		char **map = config->cub3d->map ;
		if( map[(config->cub3d->player_y  ) / config->cub3d->tile][(config->cub3d->player_x - 3) / config->cub3d->tile] == '1')
		{
			printf("walls in front of you\n");
			return ;
		}
		printf("←\n");
		config->cub3d->player_x-=3;
	}
}
int key_press_hadik(int keycode , t_data *config)
{
	if(keycode == 65307)
	{
		printf("good bye\n");
		exit(1);
	}
	if(is_key_mover2(keycode))
	{
		move_player2(keycode  , config);
		draw_shit(config);
		mlx_put_image_to_window(config->mlx , config->win ,config->img->img , 0 , 0);
	}
	return 0;
}


bool chef_raycaster(t_cub3d *cub3d)
{
	t_data *_config;
	printf("seg here \n");  

	_config = malloc(sizeof(t_data));
	_config->cub3d = cub3d ;
	_config->mlx  = mlx_init();
	_config->win =  mlx_new_window(_config->mlx  , H_WIN,W_WIN , "test");
	printf("seg here \n");  
	_config->img = malloc(sizeof(t_image));
	_config->img->img = mlx_new_image(_config->mlx, H_WIN , W_WIN);
	_config->img->adr = mlx_get_data_addr(_config->img->img  ,&_config->img->bits_per_pixel, &_config->img->line_length , &_config->img->endian );
	draw_shit(_config);
	mlx_put_image_to_window(_config->mlx , _config->win , _config->img->img , 0, 0);
	mlx_hook(_config->win, 2, 1L<<0, key_press_hadik,_config);
	mlx_loop(_config->mlx);
	return true;
}
