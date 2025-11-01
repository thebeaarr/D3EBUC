/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jari <marvin@42.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:58:41 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/11 19:58:43 by sel-jari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../src/cub3d_parser/include/parser.h"
# include "../lib/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <math.h>
# define MV_SPEED 0.075 // player spead 
# define TILE 8.0 //minimap tile
# define RAYSIZE 50.0 // minimap direaction view size
# define ROT_SPPED 0.019 // player rotation spead
# define MINIMAP_Y 800 // y location of minimap
# define MINIMAP_X 10 // x location of the minimap



/*
** ============================================================================
** 							KEY SYMBOLS ENUM
** ============================================================================
** Maps keyboard keys (9leb 3la keysym x11) to their X11 keysym values for input handling
*/
typedef enum e_keys
{
	XK_Right = 0xff53,
	XK_Left = 0xff51,
	XK_a = 0x0061,
	XK_d = 0x0064,
	XK_w = 0x0077,
	XK_s = 0x0073,
	XK_escape = 0xff1b,
}				t_keys;



/*
** ============================================================================
** 						COLOR DEFINITIONS ENUM
** ============================================================================
** predefined color values in ARGB.
** used for rendering walls, floors
*/
typedef enum e_colors
{
	BLACK = 0x00000000,
	WHITE = 0xFFFFFFFF,
	RED = 0x00FF0000,
	GREEN = 0x0099FF00,
	BLUE = 0x000000FF,
	YELLOW = 0x00FFFF00,
	CYAN = 0x0000FFFF,
	MAGENTA = 0x00FF00FF,
	ORANGE = 0x00FFA500,
	PURPLE = 0x00800080,
	GRAY = 0x00808080,
	FLOOR = 0x00404040
}				t_colors;

// mlakhdar did this .
typedef struct s_img
{
	void	*img;
	char	*adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

/*
** ==================================== ========================================
** 							ACTION STATE STRUCTURE
** ============================================================================
**tracks which movement/rotation actions are currently active
** used to handle continuous movement while keys are held down
*/
typedef struct s_action
{
	int		down;		// 1 if moving backward (S key), 0 otherwise
	int		up;        // same...
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}			t_action;

/*
** ============================================================================
** 							VECTOR STRUCTURES
** ============================================================================
*/

/* integer 2D vector (used for map coordinates,pixel positions, indexes ....), simply (2D coordinates) */
typedef struct s_vector
{
	int	x;	// x coordinate
	int	y;	//y coordinate
}			t_vector;

/* floating-point 2D vector (used for player position, ray direction), same like s_vector but for floats */
typedef struct s_vector_f
{
	float	x;
	float	y;
}			t_vector_f;

/*
** ============================================================================
** 										RAY STRUCTURE (U NEED draw_start and draw_end for texters. That's it)
** ============================================================================
** stores all data needed for a single raycast ray in DDA algorithm
** used during raycasting to determine wall intersections and distances
*/


typedef struct s_ray
{
	// for DDA RC
	t_vector	map;			// Current map grid cell being checked (not minimap, real 0,1 map)
	t_vector	step;			// Direction to step in (-1 or 1 for x and y) for dda
	t_vector_f	dir;			// normalized direction vector of the ray
	t_vector_f	sidedist;		//Distance traveled from ray start to side intersection
	t_vector_f	deltadist;		// distance between grid lines in ray direction
	float		wall_dist;		// perpendicular distance from camera plane to wall
	int			wall_x;			// X coordinate on texture (0.0 to 1.0 mapped to texture width)
	float		camera_x;		// RC (x coordinate in camera space (-1 to 1, left to right))
	int			line_height;	// height of the wall line to draw on screen , used to calculate draw_start and draw_end,
	// This is only (i think !) what you need for texters (+ image dimensions).
	int			draw_start;		// starting Y pixel for drawing the wall line
	int			draw_end;		// ending Y pixel for drawing the wall line
}				t_ray;

/*
** ============================================================================
** 								MINIMAP STRUCTURE
** ============================================================================
** 					Stores minimap-related data and positions
*/
typedef struct s_maps
{
	t_vector_f	pos;		/* Minimap position offset (not actively used) */
	t_vector	mm_frame;	/* Minimap frame dimensions (not actively used) */
}				t_maps;

/*
** ============================================================================
** 								PLAYER STRUCTURE
** ============================================================================
** 		Contains all player-related data: position, direction, movement state
*/
typedef struct s_player
{
	struct s_data	*data;
	t_action		action;		// current active actions (movement/rotation flags)
	t_vector_f		dir;		// player's forward direction vector
	t_vector_f		plane;		// Camera plane vector (perpendicular to dir, controls FOV)
	t_vector_f		pos;		// player's current position in world coordinates not pixels 
}			t_player;

/*
** ============================================================================
** 							MAIN GAME DATA STRUCTURE
** ============================================================================
** 			Central structure containing all game state and rendering data
*/

typedef struct s_data
{
	void		*mlx;			// MLX library context pointer
	void		*win;			// MLX window pointer
	t_image		*img;			// Main game frame image buffer
	t_cub3d		*cub3d;			// parsed map and texture data from .cub file
	t_player	player;			// player data and state
	int			win_width;		// window width in pixels
	int			win_height;		// window height in pixels
	int			map_height;		// map height in grid cells
	int			map_width;		// map width in grid cells
	t_vector_f	init_pos;		// Player's initial spawn position
	t_vector	mmap_center;	// Center position of the minimap in window pixels
}			t_data;

/*
** ============================================================================
** 								KEY HANDLING FUNCTIONS
** ============================================================================
*/

int		key_release(t_keys key, t_player *player);
int		key_press(t_keys key, t_player *player);
void	update_transform(t_player *player);
int		handle_close(void);
void	player_pos(t_player *player, t_keys key);
void	player_rot(t_player *player, t_keys key);
void	update_pos(t_player *player);
void	update_rot(t_player *player);

/*
** ============================================================================
** 								INITIALIZATION FUNCTIONS
** ============================================================================
*/

int		init_mlx(t_data *data);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	player_init(t_player *player);
int		get_tile_color(char c);
int		is_border(t_data *data, int x, int y, t_colors color);
void	raycast(t_data *data);

/*
** ============================================================================
** 					TEXTURE RENDERING FUNCTIONS
** ============================================================================
*/

void	draw_textured_wall(t_data *data, t_ray *ray, int x, int temp);

/*
** ============================================================================
** 							RAYCASTING ALGORITHM FUNCTIONS
** ============================================================================
*/

void	dda_inc(t_ray *ray, t_player *player);
void	dda_init(int x, t_ray *ray, t_data *data, t_player *player);
int		dda_algorithm(t_ray *ray, t_data *data);

void	calculate_wall_distance(t_ray *ray, int temp, t_data *data);

/*
** ============================================================================
** 							COLLISION DETECTION FUNCTIONS
** ============================================================================
*/

void	move_player(t_player *player, t_vector_f new);

/*
** ============================================================================
** 								MINIMAP FUNCTIONS
** ============================================================================
*/

void	minimap(t_data *data);
void	init_minimap(t_data *data);
void	draw_map_init(t_data *data);
void	draw_player_mmap(t_data *data);
void	draw_frame(t_data * data);
void	player_view(t_player *player);

/*
** ============================================================================
** 								GAME LOOP FUNCTION
** ============================================================================
*/

/* Main game loop callback - called each frame by MLX
** Renders raycast scene, minimap, and handles updates */
int		game(void *arg);

#endif
