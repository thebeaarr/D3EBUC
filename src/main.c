#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    t_data		*data;
	t_player	*player;

    if (ac != 2)
    {
        printf("ERROR: arguments\n");
        return (1);
    }
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    data->cub3d = get_file_as_struct(av[1]);
    if (!data->cub3d)
    {
        printf("ERROR: parsing\n");
        free(data);
        return (1);
    }
    if (!init_mlx(data))
    {
        printf("ERROR: mlx init\n");
        free(data->cub3d);
        free(data);
        return (1);
    }
	player = &data->player;
	player->data = data;
	player_init(&data->player);
	mlx_loop_hook(data->mlx, game, data);
    mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_hook(data->win, 2, KeyPressMask, key_press, player);
	mlx_hook(data->win, 3, KeyReleaseMask, key_release, player);
    mlx_loop(data->mlx);
    return (0);
}
