#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    t_data *data;

    if (ac != 2)
    {
        printf("ERROR: arguments\n");
        return (1);
    }

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);

    // 1) Parse map (a problem in the parsing still checking for it)
    data->cub3d = get_file_as_struct(av[1]);
    if (!data->cub3d)
    {
        printf("ERROR: parsing\n");
        free(data);
        return (1);
    }
    // print_cub3d(data->cub3d);

    // 2) Initialize MLX
    if (!init_mlx(data))
    {
        printf("ERROR: mlx init\n");
		// freeadd_exit(); later
        free(data->cub3d);
        free(data);
        return (1);
    }
	data->position.x = 0;
	data->position.y = 0;
	data->position.screen_y = 0;
	data->position.screen_x = 0;
	get_player_pos(data);
    // 3) Draw the map (2D debug)

	mlx_loop_hook(data->mlx, draw_map, data);

    mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_hook(data->win, 2, KeyPressMask, key_press, data);
	mlx_hook(data->win, 3, KeyReleaseMask, key_release, data);
    mlx_loop(data->mlx);
    return (0);
}
