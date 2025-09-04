#include "../include/parser.h"



bool map_closed(char **map)
{
	int i  = 1;
	for( ; map[i +1] ; i++)
	{
		// the first char we know that is has to be a 
		int k = 0 ;
		for(;  isspace(map[i][k]) ; k++);
		if(map[i][k] != '1')
			return false;
		for(int j = 0 ; map[i][j] ; j++)
		{
			if(isspace(map[i][j]))
			{
				if((map[i - 1][j] == '0' || map[i + 1][j] == '0' || map[i][j+1] == '0' || map[i][j - 1] == '0' ) )
					return false;
			}
			if(map[i][j] == '0' || is_player(map[i][j]))
			{
			  if((isspace(map[i-1][j]) || isspace(map[i + 1][j]) || isspace(map[i][j+1]) || isspace(map[i][j - 1]) || map[i][j + 1] == '\0' ) )
			    return false;
			}
			if(is_player(map[i][j]))
			{
				if(( map[i-1][j] == '1' && map[i + 1][j] == '1' && map[i][j+1] == '1' && map[i][j - 1] == '1' && map[i][j + 1] == '1' ) )
				{
					printf("player can't move\n");
					return false;
				}
			}
		}
	}
	for(int j = 0; map[i][j] ; j++)
	{
		if(is_player(map[i][j]) || map[i][j] == '0' )
			return false;
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
		  if(map[i][j] != '1' && map[i][j] != '0' && !is_player(map[i][j]) && !isspace(map[i][j]))
		  {
		    printf("not a valid char\n");
		    return false;
		  }
		  if(!isspace(map[i][j]))
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

