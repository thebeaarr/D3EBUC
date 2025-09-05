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
    if(is_player(c))
        return 0x00FFFF;   // cyan
    if(c == '1')
        return 0x00FF00;   // green
    if(c == '0')
        return 0x0000FF;   // blue
    if(c == ' ')
        return 0x000000;   // black
    return 0xFFFFFF;       // white for unknown chars
}

void draw_shit(t_data *_config)
{
	char **map = _config->cub3d->map;
	for(int i = 0 ; map[i] ; i++)
	{
		for(int j = 0 ; map[i][j]; j++)
		{
			int tile = 16; 
			for(int x = 0 ; x  < tile; x ++)
			{
				for(int  y = 0; y < tile ; y++)
				{
					my_mlx_pixel_put(_config->img, x + j * tile , y + i *tile , color_render(map[i][j]));
				}
			}
		}
	}
}
bool is_key_mover(int keycode)
{	
	return keycode == 97 || keycode == 115 || keycode == 100 || keycode == 119; 
}

void move_player(int keycode  , t_data *config)
{
	// valid the position 
	// then change between the chars 
	char **map = config->cub3d->map;
	int x = config->cub3d->player_x;
	int y = config->cub3d->player_y;
	int c;
	if(keycode == 97)
	{
		printf("A\n");
		if(map[y][x - 1] != '\0' && map[y][x-1] != '1')
		{
			c  = map[y][x];
			map[y][x] = '0';
			map[y][x - 1] = c;
			config->cub3d->player_x--;
		}
	}
	else if(keycode == 115)
	{
		printf("S\n");
		if(map[y - 1][x] != '\0' && map[y - 1][x] != '1')
		{
			c  = map[y][x];
			map[y][x] = '0';
			map[y - 1][x] = c;
			config->cub3d->player_y--;
		}
	}
	else if(keycode == 119)
	{
		printf("W\n");
		if(map[y + 1][x] != '\0' && map[y + 1][x] != '1')
		{
			c  = map[y][x];
			map[y][x] = '0';
			map[y + 1][x] = c;
			config->cub3d->player_y++;
		}
	}
	else if(keycode == 100)
	{
		printf("D\n");
		if(map[y][x + 1] != '\0' && map[y][x+1] != '1')
		{
			c  = map[y][x];
			map[y][x] = '0';
			map[y][x + 1] = c;
			config->cub3d->player_x++;
		}	
	}
}


int key_press_handler(int keycode, t_data *config)
{
	if(keycode == 65307)
	{
		printf("good bye\n");
		exit(1);
	}
	if(is_key_mover(keycode))
	{
		move_player(keycode  , config);
		draw_shit(config);
		mlx_put_image_to_window(config->mlx , config->win ,config->img->img , 0 , 0);
	}
  return (0);
}

int key_release_handler(int keycode)
{
    printf("Key %d was released UP!\n", keycode);
    return (0);
}


int mouse_click_handler(int button, int x, int y)
{
    printf("Mouse button %d clicked at position (%d, %d)\n", button, x, y);
    if (button == 1)        // Left click
        printf("Left mouse button clicked!\n");
    else if (button == 2)   // Middle click 
        printf("Middle mouse button clicked!\n");
    else if (button == 3)   // Right click
        printf("Right mouse button clicked!\n");
    return (0);
}

bool chef_raycaster(t_cub3d *cub3d)
{
	t_data *_config;
	printf("seg here \n");  

	_config = malloc(sizeof(t_data));
	_config->cub3d = cub3d ;
	// find the positino of the player first ( sorry i have to get it first from her ? hahah )
	_config->mlx  = mlx_init();
	_config->win =  mlx_new_window(_config->mlx  , 500 , 300 , "test");
	printf("seg here \n");  
	_config->img = malloc(sizeof(t_image));
	_config->img->img = mlx_new_image(_config->mlx, 500 , 300);
	_config->img->adr = mlx_get_data_addr(_config->img->img  ,&_config->img->bits_per_pixel, &_config->img->line_length , &_config->img->endian );
	// printf("--%x --- %d--- %d---\n", ++*_config->img->adr++ , _config->img->line_length ,_config->img->endian);
	// u trying to tell me that the adr is nothign ??  is a space then okay 
	/// that's toought
	// for(int i = 0 ;_config->img->adr ; i++)
	// 	printf("%c\n" , _config->img->adr[i]);
	// that's not good hhhhhh 
	// anyway try to crazy hhh
	draw_shit(_config);
	mlx_put_image_to_window(_config->mlx , _config->win , _config->img->img , 0, 0);
    mlx_hook(_config->win, 2, 1L<<0, key_press_handler,_config);
	// mlx_hook(_config->win, 4, 1L<<2, mouse_click_handler , NULL);
	mlx_loop(_config->mlx);
	return true;
}

