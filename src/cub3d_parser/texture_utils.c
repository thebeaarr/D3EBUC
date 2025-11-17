/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:50:14 by madhat            #+#    #+#             */
/*   Updated: 2025/11/17 20:22:41 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_txt(char *line)
{
	if (!ft_strncmp(line, "NO", 2) && isspace(line[2]))
		return (1);
	if (!ft_strncmp(line, "SO", 2) && isspace(line[2]))
		return (2);
	if (!ft_strncmp(line, "WE", 2) && isspace(line[2]))
		return (3);
	if (!ft_strncmp(line, "EA", 2) && isspace(line[2]))
		return (4);
	return (0);
}

bool	check_ntxt(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 2)
		return (false);
	return (true);
}

bool	path_valid(char *str)
{
	char	*extension;
	int		fd;

	extension = strrchr(str, '.');
	if (!extension || strcmp(extension, ".xpm") != 0)
		return (false);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}
