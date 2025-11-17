#include "../../cub3d.h"

void	free_all(t_data *data)
{
	printf("salam");
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	/*checki data->cub3d fiha chi l3ibat khesshoum free*/
	// free(data->cub3d->map);
	// free(data->cub3d);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}