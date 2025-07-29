/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:44:19 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/11/30 18:44:20 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// merging if for the ft_strlen and check_nl
size_t	merging(const char *s, int mode)
{
	size_t	i;

	i = 0;
	if (mode == 1)
	{
		if (!s)
			return (0);
		while (s[i])
			i++;
	}
	else
	{
		while (s[i] != '\n' && s[i])
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

char	*get_line(char *buffer, int i)
{
	char	*line;
	int		j;

	line = ft_calloc((size_t)i + 1, 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	return (line);
}

char	*trim_the_buffer(char *buffer, int i)
{
	char	*new_buffer;

	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i);
	free(buffer);
	return (new_buffer);
}

char	*read_and_manage_buffer(int fd, char **buffer)
{
	char	*s;
	char	*temp;
	int		read_b;

	s = ft_calloc((size_t)BUFFER_SIZE + 1, 1);
	if (!s)
		return (NULL);
	read_b = read(fd, s, BUFFER_SIZE);
	while (read_b > 0)
	{
		s[read_b] = '\0';
		temp = *buffer;
		*buffer = ft_strjoin(temp, s);
		free(temp);
		if (merging((const char *)*buffer, 0) < merging((const char *)*buffer,
				1))
			break ;
		read_b = read(fd, s, BUFFER_SIZE);
	}
	free(s);
	return (*buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[FDS_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd > FDS_MAX)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, 1);
	buffer[fd] = read_and_manage_buffer(fd, &buffer[fd]);
	if (!buffer[fd] || *buffer[fd] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = get_line(buffer[fd], merging((const char *)buffer[fd], 0));
	buffer[fd] = trim_the_buffer(buffer[fd], merging((const char *)(buffer[fd]),
				0));
	return (line);
}
