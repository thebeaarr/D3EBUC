/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:06:28 by madhat            #+#    #+#             */
/*   Updated: 2025/11/20 18:14:19 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	dup_c(t_file *head)
{
	t_file	*current;
	char	*tmp;
	int		index;
	int		count_f;
	int		count_c;

	current = head;
	count_f = 0;
	count_c = 0;
	while (current)
	{
		tmp = current->line;
		index = 0;
		while (isspace(tmp[index]))
			index++;
		if (!strncmp("F", tmp + index, 1) && isspace(tmp[index + 1]))
			count_f++;
		else if (!strncmp("C", tmp + index, 1) && isspace(tmp[index + 1]))
			count_c++;
		if (count_f > 1 || count_c > 1)
			return (true);
		current = current->next;
	}
	return (count_f != 1 || count_c != 1);
}

void	free_gnl(char *line, int fd)
{
	if (line)
		free(line);
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
	line = NULL;
	close(fd);
}

bool	check_v(char *s)
{
	int	virgule;
	int	index;

	index = 0;
	virgule = 0;
	while (s[index])
	{
		if (s[index] == ',')
			virgule++;
		index++;
	}
	if (virgule != 2)
		return (false);
	return (true);
}
