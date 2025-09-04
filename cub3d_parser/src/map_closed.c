#include "../include/parser.h"



// bool map_closed(char **map)
// {
// 	int i  = 1;
// 	for( ; map[i +1] ; i++)
// 	{
// 		// the first char we know that is has to be a 
// 		int k = 0 ;
// 		for(;  map[i][k] == 32 ; k++);
// 		if(map[i][k] != '1')
// 			return false;
// 		for(int j = 0 ; map[i][j] ; j++)
// 		{
// 			if(map[i][j] == 32)
// 			{
// 				if((map[i - 1][j] == '0' || map[i + 1][j] == '0' || map[i][j+1] == '0' || map[i][j - 1] == '0' ) )
// 					return false;
// 			}
// 			if(map[i][j] == '0' || is_player(map[i][j]))
// 			{
// 				if(((ft_strlen(map[i]) > ft_strlen(map[i + 1]) && ft_strlen(map[i]) > ft_strlen(map[i  - 1]) ) ||map[i-1][j] == 32 || map[i + 1][j] == 32 || map[i][j+1] == 32 || map[i][j - 1] == 32 || map[i][j + 1] == '\0' ) )
// 				{
// 					printf("player may escape the map\n");
// 					return false;
// 				}
// 			}
// 			if(is_player(map[i][j]))
// 			{
// 				if(( map[i-1][j] == '1' && map[i + 1][j] == '1' && map[i][j+1] == '1' && map[i][j - 1] == '1' && map[i][j + 1] == '1' ) )
// 				{
// 					printf("player can't move\n");
// 					return false;
// 				}
// 			}
// 		}
// 	}
// 	for(int j = 0; map[i][j] ; j++)
// 	{
// 		if(is_player(map[i][j]) || map[i][j] == '0' )
// 			return false;
// 	}

// 	return true;
// }

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

	bool is_player(char c); // your helper

// Safe neighbor access (handles ragged rows)
char get_cell(char **map, int i, int j, int rows)
{
    if (i < 0 || i >= rows) return ' ';
    if (j < 0 || j >= (int)strlen(map[i])) return ' ';
    return map[i][j];
}

// Check if a zero or player is next to a space (hole)
bool has_hole(char **map, int i, int j, int rows)
{
    if (get_cell(map, i-1, j, rows) == ' ') return true;
    if (get_cell(map, i+1, j, rows) == ' ') return true;
    if (get_cell(map, i, j-1, rows) == ' ') return true;
    if (get_cell(map, i, j+1, rows) == ' ') return true;
    return false;
}

// Check if a player is completely trapped by walls
bool player_trapped(char **map, int i, int j, int rows)
{
    if (!is_player(map[i][j])) return false;
    if (get_cell(map, i-1, j, rows) != '1') return false;
    if (get_cell(map, i+1, j, rows) != '1') return false;
    if (get_cell(map, i, j-1, rows) != '1') return false;
    if (get_cell(map, i, j+1, rows) != '1') return false;
    return true;
}

// Main function to check if map is closed
bool map_closed(char **map)
{
    int rows = 0;
    while (map[rows])
        rows++;

    int i = 0;
    while (i < rows)
    {
        int j = 0;
        while (j < (int)strlen(map[i]))
        {
            char c = map[i][j];
            if (c == '0' || is_player(c))
            {
                if (has_hole(map, i, j, rows))
                {
                    printf("player or zero may escape the map\n");
                    return false;
                }
                if (player_trapped(map, i, j, rows))
                {
                    printf("player can't move\n");
                    return false;
                }
            }
            j++;
        }
        i++;
    }
    return true;
}

bool parse_map(char **map)
{	
	int count_p  =0;
	for(int i = 0; map[i] ;i++)
	{
		for(int k =0 ; map[i][k];k++)
		{
		  if(is_player(map[i][k]))
		    count_p++;
		}
	}
	if(count_p != 1)
	{
		printf("ERROR:player not exist or there is multiple player\n");
		return false;
	}
	for(int i = 0 ; map[i] ; i++)
	{
		if(map[i][0] == '\n')
		{
		  printf("empty line\n");
		  return false;
		}
		int j = 0;
		for(; map[i][j] ; j++)
		{
		  if(map[i][j] != '1' && map[i][j] != '0' && !is_player(map[i][j]) && map[i][j] != 32)
		  {
		    printf("not a valid char\n");
		    return false;
		  }
		  if(map[i][j] != 32)
		    break;
		}
		if(map[i][j] == '\0' || map[i][j] == '\n')
		{
			printf("no walls\n");
			return false;
		}
		if(!map_closed(map))
			return false;
	}
	return true;
}	

