#include "../../cub3d.h" 

static bool	read_map(int fd, t_list *list, char *tmp)
{
	t_file	*line;

	if (tmp == NULL)
	{
		printf("incomplete map\n");
		free_list(list);
		return (false);
	}
	list->head_s = anode(tmp);
	free(tmp);
	while ((tmp = get_next_line(fd)))
	{
		line = anode(tmp);
		add_back(&list->head_s, line);
		free(tmp);
	}
	return (true);
}

t_list	*read_file(char *path)
{
	t_list	*list;
	char	*tmp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR: failed to open file\n");
		return (NULL);
	}
	list = NULL;
	if (!read_config(fd, &list, &tmp))
	{
		close(fd);
		return (NULL);
	}
	if (!read_map(fd, list, tmp))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (list);
}
