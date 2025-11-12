#include "../../cub3d.h"

static bool	is_empty_line(char *line)
{
	if (line[0] == '\n' || isspaces(line))
		return (true);
	return (false);
}

static bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '1' || line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (true);
	return (false);
}

static int	skip_leading_spaces(char *line)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	return (i);
}

t_list	*init_list(char *line)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head_f = anode(line);
	list->head_s = NULL;
	return (list);
}

bool	read_config(int fd, t_list **list, char **tmp)
{
	t_file	*line;
	int		i;

	while ((*tmp = get_next_line(fd)))
	{
		if (is_empty_line(*tmp))
		{
			free(*tmp);
			continue;
		}
		if (is_map_line(*tmp))
			break;
		i = skip_leading_spaces(*tmp);
		line = anode(*tmp + i);
		if (!*list)
			*list = init_list(*tmp + i);
		else
			add_back(&(*list)->head_f, line);
		free(*tmp);
	}
	if (size_list((*list)->head_f) > 6)
		return (free_list(*list), false);
	return (true);
}
