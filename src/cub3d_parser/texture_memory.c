/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:49:57 by madhat            #+#    #+#             */
/*   Updated: 2025/11/12 10:49:58 by madhat           ###   ########.fr       */
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
