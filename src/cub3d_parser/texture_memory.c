/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:49:57 by madhat            #+#    #+#             */
/*   Updated: 2025/11/19 17:06:28 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}
