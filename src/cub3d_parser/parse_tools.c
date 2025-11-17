/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:40:13 by madhat            #+#    #+#             */
/*   Updated: 2025/11/17 19:39:26 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	path_cub(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (extension == NULL)
		return (false);
	if (ft_strcmp(extension, ".cub") == 0)
		return (true);
	return (false);
}

int	ft_strcmp(char *ext, char const *tst)
{
	int	i;

	i = 0;
	while (ext[i] && tst[i])
	{
		if (ext[i] != tst[i])
			return (1);
		i++;
	}
	if (ext[i] != '\0' || tst[i] != '\0')
		return (1);
	return (0);
}
