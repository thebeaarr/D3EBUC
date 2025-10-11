#include "cub3d.h"

int	handle_close(void)
{
	printf("cub3D closed\n");
	exit(1);
}

void	player_pos(t_player *player, t_keys key)
{
	if (key == XK_s)
	{
		player->action.up = 0;
		player->action.down = 1;
	}
	else if (key == XK_w)
	{
		player->action.down = 0;
		player->action.up = 1;
	}
	else if (key == XK_a)
	{
		player->action.right = 0;
		player->action.left = 1;
	}
	else if (key == XK_d)
	{
		player->action.left = 0;
		player->action.right = 1;
	}
}

void	player_rot(t_player *player, t_keys key)
{
	if (key == XK_Left)
	{
		player->action.rot_left = 1;
		player->action.rot_right= 0;
	}
	else if (key == XK_Right)
	{
		player->action.rot_right = 1; 
		player->action.rot_left = 0; 
	}
}

static int	not_wall(t_player *player, float x, float y)
{
	char	**map;
	
	map = player->data->cub3d->map;
	if (map[(int)floor(y - 0.5)][(int)floor(x - 0.5)] == '1')
		return (0);
	if (map[(int)ceil(y - 0.5)][(int)ceil(x - 0.5)] == '1')
		return (0);
	if (map[(int)floor(y - 0.5)][(int)ceil(x - 0.5)] == '1')
		return (0);
	if (map[(int)ceil(y - 0.5)][(int)floor(x - 0.5)] == '1')
		return (0);
	
	return (1);
}

void	move_player(t_player *player, float x, float y)
{
	if (not_wall(player, x, y))
	{
		player->pos.x = x;
		player->pos.y = y;
	}
}

void	update_pos(t_player *player)
{
	float	new_x, new_y;
	
	if (player->action.right)
	{
		new_x = player->pos.x - player->dir.y * MV_SPEED;
		new_y = player->pos.y + player->dir.x * MV_SPEED;
		move_player(player, new_x, new_y);
	}
	if (player->action.left)
	{
		new_x = player->pos.x + player->dir.y * MV_SPEED;
		new_y = player->pos.y - player->dir.x * MV_SPEED;
		move_player(player, new_x, new_y);
	}
	if (player->action.down)
	{
		new_x = player->pos.x - player->dir.x * MV_SPEED;
		new_y = player->pos.y - player->dir.y * MV_SPEED;
		move_player(player, new_x, new_y);
	}
	if (player->action.up)
	{
		new_x = player->pos.x + player->dir.x * MV_SPEED;
		new_y = player->pos.y + player->dir.y * MV_SPEED;
		move_player(player, new_x, new_y);
	}
}

void	update_rot(t_player *player)
{
	float	temp;
	float	rot_angle;

	if (player->action.rot_left)
	{
		rot_angle = -ROT_SPPED; // Left rotation (positive angle)
		temp = player->dir.x;
		player->dir.x = player->dir.x * cos(rot_angle) - player->dir.y * sin(rot_angle);
		player->dir.y = temp * sin(rot_angle) + player->dir.y * cos(rot_angle);
		temp = player->plane.x;
		player->plane.x = player->plane.x * cos(rot_angle) - player->plane.y * sin(rot_angle);
		player->plane.y = temp * sin(rot_angle) + player->plane.y * cos(rot_angle);
	}
	if (player->action.rot_right)
	{
		rot_angle = ROT_SPPED; // Right rotation (negative angle)
		temp = player->dir.x;
		player->dir.x = player->dir.x * cos(rot_angle) - player->dir.y * sin(rot_angle);
		player->dir.y = temp * sin(rot_angle) + player->dir.y * cos(rot_angle);
		temp = player->plane.x;
		player->plane.x = player->plane.x * cos(rot_angle) - player->plane.y * sin(rot_angle);
		player->plane.y = temp * sin(rot_angle) + player->plane.y * cos(rot_angle);
	}
}