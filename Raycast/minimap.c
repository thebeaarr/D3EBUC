#include "cub3d.h"

static int gett_color(char c)
{
	if (c == '1')
		return (WHITE);
	if (c == '0')
		return (BLACK);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (ORANGE);
	return (GREEN);
}

static void	borders_stop(t_data *data, int x, int y)
{
	t_player	*player;

	player = &data->player;
	if (x == 0 && data->img->adr[(player->y * data->img->line_length + (player->x + 39) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_x -= MV_SPEED;
	if (x == 0 && data->img->adr[(player->y * data->img->line_length + (player->x) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_x += MV_SPEED;
	if (y == 0 && data->img->adr[((player->y + 39) * data->img->line_length + (player->x) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_y -= MV_SPEED;
	if (y == 0 && data->img->adr[((player->y)* data->img->line_length + (player->x) * (data->img->bits_per_pixel / 8))] == (char)WHITE)
		data->position.screen_y += MV_SPEED;
}

static int	draw_map_init(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
    char **map;

	map = data->cub3d->map;
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j] && map[i][j] != '\n'; j++)
        {
            int color = gett_color(map[i][j]);
			if (color == ORANGE)
				color = BLACK;
			for (int y = 0; y < TILE; y++)
			{
				for (int x = 0; x < TILE; x++)
					my_mlx_pixel_put(data->img,j * TILE + x,i * TILE + y,color);
			}
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

int	draw_map(void *arg)
{
	t_data 		*data;
	t_player	*player;
	char		**map;
 	int			color;
	int			i;
	int			j;
	int			x;
	int			y;

	data = (t_data *)arg;
	player	= &data->player;
    map = data->cub3d->map;
	draw_map_init(data);
	i = 0;
    while(map[i])
    {
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
        {
			color = gett_color(map[i][j]);
			y = 0;
			while (color == ORANGE && y < TILE)
			{
				x = 0;
				while (x < TILE)
				{
					player->x = j * TILE + x + (int)data->position.screen_x;
					player->y = i * TILE + y + (int)data->position.screen_y;
					borders_stop(data, x ,y);
					my_mlx_pixel_put(data->img, player->x , player->y, color);
					x++;
				}
				y++;
			}
			j++;
        }
		i++;
    }
	update_movement(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}