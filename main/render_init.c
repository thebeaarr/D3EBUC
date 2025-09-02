#include "../mlx_init/include/cub3d_mlx.h"

int init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return (0);

    data->win = mlx_new_window(data->mlx, 1000, 800, "Cub3D");
    if (!data->win)
        return (0);

    data->img = malloc(sizeof(t_image));
    if (!data->img)
	{
    	return (0);
	}
	data->img->img = mlx_new_image(data->mlx, 1000, 800);
    data->img->adr = mlx_get_data_addr(data->img->img,
        &data->img->bits_per_pixel,
        &data->img->line_length,
        &data->img->endian);
    return (1);
}