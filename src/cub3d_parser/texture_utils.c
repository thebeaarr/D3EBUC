#include "../../cub3d.h"

int		is_txt(char *line)
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
	{
		printf("extension path .xpm\n");
		return (false);
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		printf("file cannot be open\n");
		return (false);
	}
	close(fd);
	return (true);
}
