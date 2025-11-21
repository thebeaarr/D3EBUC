/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texutres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:41:39 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/19 17:52:55 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	tex;

	tex.data.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);
	if (!tex.data.img)
	{
		print_error("Error: Failed to load texture from path: ");
		print_error(path);
		print_error("\n");
		exit(EXIT_FAILURE);
	}
	tex.data.adr = mlx_get_data_addr(tex.data.img, &tex.data.bits_per_pixel,
			&tex.data.line_length, &tex.data.endian);
	return (tex);
}

int	get_index(char ***textures, int i)
{
	int		index;
	int		j;
	char	*a;

	index = -1;
	j = 0;
	if (i == 0)
		a = ft_strdup("NO");
	else if (i == 1)
		a = ft_strdup("SO");
	else if (i == 2)
		a = ft_strdup("WE");
	else if (i == 3)
		a = ft_strdup("EA");
	while (j < 4)
	{
		if (strcmp(textures[j][0], a) == 0)
			index = j;
		j++;
	}
	free(a);
	return (index);
}

bool	load_textures(t_data *data)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < 4)
	{
		index = get_index(data->cub3d->textures, i);
		if (index == -1)
			return (false);
		data->texture[i] = load_texture(data->mlx,
				data->cub3d->textures[index][1]);
		i++;
	}
	return (true);
}
