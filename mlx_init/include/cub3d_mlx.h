#ifndef CUB3D_MLX_H
# define CUB3D_MLX_H

#include <stdio.h>
#include <stdlib.h>
#include "../../cub3d_parser/include/parser.h"
#include "../../minilibx-linux/mlx.h"
#include <X11/X.h>

typedef enum e_keys
{
	XK_Right = 0xff53,
	XK_Left = 0xff51,
	XK_a = 0x0061,
	XK_d = 0x0064,
	XK_w = 0x0077,
	XK_s = 0x0073,
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
}				t_position;

typedef struct s_movement
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	rot_left;
	int	rot_right;
	float	speed;
}				t_movement;

typedef struct s_img 
{
	void 	*img;
	char 	*adr; 
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_data
{
  void			*mlx;
  void			*win;
  t_position	position;
  t_movement	movement;
  float			angle;
  t_image		*img;
  t_cub3d		*cub3d;
}t_data;

/* key handling */
int 	key_release(t_keys key , t_data *data);
int 	key_press(t_keys key , t_data *data);
int 	handle_close();
void	update_movement(t_data *data);
void	draw_direction_line(t_data *data);
void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);

int		init_mlx(t_data *data);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void  	draw_2d(t_data *data);
int		draw_map_init(void *arg);
int		draw_map(void *arg);
#endif
