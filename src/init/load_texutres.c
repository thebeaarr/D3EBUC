/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texutres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:41:39 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/21 22:10:39 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_help(t_data *data, int nbloads)
{
	int	i;

	i = 0;
	print_error("Error: Failed to load texture from path\n");
	while (i < nbloads)
	{
		mlx_destroy_image(data->mlx, data->texture[i].data.img);
		i++;
	}
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_display(data->mlx);
	free(data->img);
	free_dptr(data->cub3d->map);
	free_tptr(data->cub3d->textures, 4);
	free(data->cub3d);
	free(data->mlx);
	free(data);
	exit(EXIT_FAILURE);
}

t_texture	load_texture(t_data *data, void *mlx, char *path, int nbloads)
{
	t_texture	tex;

	tex.data.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);
	if (!tex.data.img)
		free_help(data, nbloads);
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
		data->texture[i] = load_texture(data, data->mlx,
				data->cub3d->textures[index][1], i);
		i++;
	}
	return (true);
}
