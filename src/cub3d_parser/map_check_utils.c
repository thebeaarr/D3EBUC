#include "../../cub3d.h"

bool	is_valid_char(char c)
{
	if (is_player(c))
		return (true);
	if (c == '0' || c == '1' || c == ' ')
		return (true);
	return (false);
}

bool	line_has_walls(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	if (line[j] == '\0')
		return (printf("no walls\n"), false);
	return (true);
}

bool	check_line_chars(char *line, int *player_count)
{
	int	j;

	if (line[0] == '\n' || line[0] == '\0')
		return (printf("empty line\n"), false);
	j = 0;
	while (line[j])
	{
		if (is_player(line[j]))
			(*player_count)++;
		else if (!is_valid_char(line[j]))
			return (printf("not a valid char\n"), false);
		j++;
	}
	return (true);
}

bool	c_player(int player_count)
{
	if (player_count != 1)
	{
		printf("ERROR: player not exist or multiple players\n");
		return (false);
	}
	return (true);
}
