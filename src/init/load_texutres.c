/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texutres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:41:39 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/09 04:42:42 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	tex;

	tex.data.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);
	if (!tex.data.img)
		printf("Failed to load texture");
	tex.data.adr = mlx_get_data_addr(tex.data.img, &tex.data.bits_per_pixel,
			&tex.data.line_length, &tex.data.endian);
	return (tex);
}

bool	load_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i] = load_texture(data->mlx,
				data->cub3d->textures[i][1]);
		if (!data->texture[i].data.img)
			return (false);
		i++;
	}
	return (true);
}
