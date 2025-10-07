#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../cub3d_parser/include/parser.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <math.h>
# define MV_SPEED 0.075
# define TILE 20.0
# define CENTER TILE / 2 - 1
# define ROT_SPPED 0.019
# define RAYSIZE 50.0
# define BORDER 0xFFFFFFFF

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
    GREEN   = 0x0099FF00,
    BLUE    = 0x000000FF,
    YELLOW  = 0x00FFFF00,
    CYAN    = 0x0000FFFF,
    MAGENTA = 0x00FF00FF,
    ORANGE  = 0x00FFA500,
    PURPLE  = 0x00800080,
    GRAY    = 0x00808080
}				t_colors;

typedef struct s_img 
{
	void 	*img;
	char 	*adr; 
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_action
{
	int		down;
	int		up;
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}			t_action;

typedef struct s_vector
{
	int	x;
	int	y;
}			t_vector;

typedef struct s_vector_f
{
	float	x;
	float	y;
}			t_vector_f;

typedef struct s_raycast
{
	t_vector	map;
	t_vector	step;
	t_vector_f	delta;
	t_vector_f	dir;
}				t_raycast;

typedef struct s_maps
{
	t_vector_f	pos;
}				t_maps;

typedef struct s_player
{
	struct s_data	*data;
  	t_action		action;
	t_vector_f		dir;
	t_vector_f		pos;
	float			angle;
	int				moved;
	t_maps			mmap;
}			t_player;



typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_image			*img;
	t_cub3d			*cub3d;
	t_player		player;

}t_data;


/* key handling */
int 	key_release(t_keys key, t_player *player);
int 	key_press(t_keys key, t_player *player);
void	update_movement(t_player *player);
int 	handle_close();
void	player_pos(t_player *player, t_keys key);
void	player_rot(t_player *player, t_keys key);
void	update_pos(t_player *player);
void	update_rot(t_player *player);
int		handle_close(void);


void	player_view(t_player *player);

/* Init cub3D*/
int		init_mlx(t_data *data);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	player_init(t_player *player);
int		gett_color(char c);
int		draw_minimap(void *arg);
int		is_border(t_data *data, int x, int y);
#endif
