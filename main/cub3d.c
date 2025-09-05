#include "../cub3d_parser/include/parser.h"
#include "../mlx_init/include/cub3d_mlx.h"
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
	chef_raycaster(cub3d);
	return 0;
}
