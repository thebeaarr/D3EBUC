#include "../include/parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


static char get_cell(char **map, int i, int j, int rows)
{
    if (i < 0 || i >= rows) return ' ';
    if (j < 0 || j >= (int)strlen(map[i])) return ' ';
    return map[i][j];
}

static bool has_hole(char **map, int i, int j, int rows)
{
    if (get_cell(map, i - 1, j, rows) == ' ') return true;
    if (get_cell(map, i + 1, j, rows) == ' ') return true;
    if (get_cell(map, i, j - 1, rows) == ' ') return true;
    if (get_cell(map, i, j + 1, rows) == ' ') return true;
    return false;
}

static bool player_trapped(char **map, int i, int j, int rows)
{
    if (get_cell(map, i - 1, j, rows) != '1') return false;
    if (get_cell(map, i + 1, j, rows) != '1') return false;
    if (get_cell(map, i, j - 1, rows) != '1') return false;
    if (get_cell(map, i, j + 1, rows) != '1') return false;
    return true;
}


bool map_closed(char **map)
{
	int rows = 0;
	while (map[rows])
		rows++;
	int i = 0;
	while (i < rows)
	{
		int j = 0;
		while (map[i][j])
		{
			char c = map[i][j]; 
			if (c == '0' || is_player(c))
			{
				if (has_hole(map, i, j, rows))
				{
					printf("player or zero may escape the map\n");
					return false;
				}
			}
			if (is_player(c) && player_trapped(map, i, j, rows))
			{
				printf("player can't move\n");
				return false;
			}
			j++;
		}
		i++;
	}
	return true;
}


bool parse_map(char **map)
{
	int player_count = 0;
	int i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n' || map[i][0] == '\0')
		{
			printf("empty line\n");
			return false;
		}
		int j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				player_count++;
			else if (  map[i][j] != '0' &&  map[i][j] != '1' &&  map[i][j] != 32)
			{
				printf("not a valid char\n");
				return false;
			}
			j++;
		}
		j = 0;
		while (map[i][j] == 32)
			j++;
		if (map[i][j] == '\0')
		{
			printf("no walls\n");
			return false;
		}
		i++;
	}
	if(player_count != 1)
	{
		printf("ERROR: player not exist or multiple players\n");
		return false;
	}
	if (!map_closed(map))
		return false;
	return true;
}
