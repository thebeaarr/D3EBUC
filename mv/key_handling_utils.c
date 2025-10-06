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

void	update_pos(t_player *player)
{
	if (player->action.right)
	{
		player->pos.x -= player->dir.y * MV_SPEED;
		player->pos.y += player->dir.x * MV_SPEED;
	}
	if (player->action.left)
	{
		player->pos.x += player->dir.y * MV_SPEED;
		player->pos.y -= player->dir.x * MV_SPEED;
	}
	if (player->action.down)
	{
		player->pos.x -= player->dir.x * MV_SPEED;
		player->pos.y -= player->dir.y * MV_SPEED;
	}
	if (player->action.up)
	{
		player->pos.x += player->dir.x * MV_SPEED;
		player->pos.y += player->dir.y * MV_SPEED;
	}
}

void	update_rot(t_player *player)
{
	float temp;

	if (player->action.rot_left)
	{
		player->angle = -ROT_SPPED;
		temp = player->dir.x;
		player->dir.x = player->dir.x * cosf(player->angle) - player->dir.y * sinf(player->angle);
		player->dir.y = temp * sinf(player->angle) + player->dir.y * cosf(player->angle);
	}
	if (player->action.rot_right)
	{
		player->angle = ROT_SPPED;
		temp = player->dir.x;
		player->dir.x = player->dir.x * cosf(player->angle) - player->dir.y * sinf(player->angle);
		player->dir.y = temp * sinf(player->angle) + player->dir.y * cosf(player->angle);
	}
}