#include "../../cub3d.h"

void	free_all(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_image(data->mlx , data->texture[0].data.img);
	mlx_destroy_image(data->mlx , data->texture[1].data.img);
	mlx_destroy_image(data->mlx , data->texture[2].data.img);
	mlx_destroy_image(data->mlx , data->texture[3].data.img);
	mlx_destroy_display(data->mlx);
	free(data->img);
	free_dptr(data->cub3d->map);
	free_tptr(data->cub3d->textures, 4);
	free(data->cub3d);
	free(data->mlx);
	free(data);
	exit(EXIT_SUCCESS);
}
