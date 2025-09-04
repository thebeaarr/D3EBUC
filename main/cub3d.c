#include "../cub3d_parser/include/parser.h"
#include "../mlx_init/include/cub3d_mlx.h"

void free_cub3d(t_cub3d *cub3d)
{
	free_dptr(cub3d->map);
	free_tptr(cub3d->textures , 4);
	free(cub3d);
}

int main(int ac , char **av)
{
	if(ac != 2)
	{
		printf("ERROR: ./cub3d <path>\n");
		return 1;
	}
	t_cub3d *cub3d ;
	cub3d = get_file_as_struct(av[1]);
	if(cub3d == NULL)
		return 1;
	t_data *data = malloc(sizeof(t_data));
	if(data == NULL)
	{
		free_cub3d(cub3d);
		return 1;
	}
	// data->mlx = mlx_init();
	// data->win = mlx_new_window(data->mlx , 400 , 200 , "test" );
	// data->img->img = mlx_new_image(data->mlx , 2 , 2);
	// data->img->adr = mlx_get_data_addr(data->img->img , &data->img->bits_per_pixel , &data->img->line_length , &data->img->endian);
	return 0;
}
