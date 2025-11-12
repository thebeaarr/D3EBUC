#include "../../cub3d.h"

void	free_dptr(char **txt)
{
	int	index;

	index = 0;
	while (txt[index])
	{
		free(txt[index]);
		index++;
	}
	free(txt);
	txt = NULL;
}

void	free_tptr(char ***textures, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		free_dptr(textures[index]);
		index++;
	}
	free(textures);
	textures = NULL;
}
