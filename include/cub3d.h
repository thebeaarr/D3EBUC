#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include "../cub3d_parser/include/parser.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
# define MV_SPEED 1.0;
# define TILE 40

typedef enum e_keys
{
	XK_Right = 0xff53,
	XK_Left = 0xff51,
	XK_a = 0x0061,
	XK_d = 0x0064,
	XK_w = 0x0077,
	XK_s = 0x0073,
	XK_escape = 0xff1b,
}             t_keys;
 
typedef enum e_colors
{
	BLACK   = 0x00000000,
    WHITE   = 0xFFFFFFFF,
    RED     = 0x00FF0000,
    GREEN   = 0x0000FF00,
    BLUE    = 0x000000FF,
    YELLOW  = 0x00FFFF00,
    CYAN    = 0x0000FFFF,
    MAGENTA = 0x00FF00FF,
    ORANGE  = 0x00FFA500,
    PURPLE  = 0x00800080,
    GRAY    = 0x00808080
}				t_colors;

typedef struct s_position
{
	int	x;
	int y;
	float	screen_x;
	float	screen_y; 
}				t_position;

typedef struct s_img 
{
	void 	*img;
	char 	*adr; 
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_player
{
	int	init_x;
	int	init_y;
	int	x;
	int	y;
}			t_player;
typedef struct s_data
{
  void			*mlx;
  void			*win;
  t_position	position;
  t_image		*img;
  t_cub3d		*cub3d;
  t_player		player;
}t_data;

/* key handling */
int 	key_release(t_keys key , t_data *data);
int 	key_press(t_keys key , t_data *data);
void	update_movement(t_data *data);
int 	handle_close();

/* Init cub3D*/
int		init_mlx(t_data *data);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	get_player_pos(t_data *data);
int		gett_color(char c);

int		draw_map(void *arg);
#endif
