/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:22:42 by madhat            #+#    #+#             */
/*   Updated: 2025/11/17 19:39:03 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	count_colors(char **color)
{
	int	count;

	count = 0;
	while (color[count])
		count++;
	return (count);
}

static void	free_colors(char **color, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(color[i]);
		i++;
	}
	free(color);
}

static bool	validate_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (false);
	if (g < 0 || g > 255)
		return (false);
	if (b < 0 || b > 255)
		return (false);
	return (true);
}

static int	parse_rgb(char **color)
{
	int	r;
	int	g;
	int	b;
	int	rgb;

	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (!validate_rgb(r, g, b))
		return (-1);
	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}

int	get_color(char *s)
{
	char	*str;
	char	**color;
	int		count;
	int		rgb;

	if (!s)
		return (-1);
	str = rm_spaces_check(s);
	if (!str)
		return (-1);
	color = ft_split(str, ',');
	free(str);
	if (!color)
		return (-1);
	count = count_colors(color);
	if (count != 3)
		return (free_colors(color, count), -1);
	rgb = parse_rgb(color);
	free_colors(color, count);
	return (rgb);
}
