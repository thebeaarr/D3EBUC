#include "../include/parser.h"

bool path_cub(char *path)
{
	char *extension;

	extension = ft_strrchr(path , '.');
	if(strcmp(extension  , ".cub") == 0)
		return true;
	return false;
}
t_cub3d *get_file_as_struct(char *path)
{
	t_cub3d *store;
	store = NULL;
	if(!path_cub(path))
		return NULL;
	t_list *list = read_file(path);
	store = malloc(sizeof(t_cub3d));
	if(list == NULL || list->head_f == NULL || list->head_s == NULL)
	{
		printf("ERROR");
		return NULL;
	}
	store->textures = get_textures(list->head_f);
	if(store->textures == NULL)
	{
		free_list(list);
		free(store);
		return NULL;
	}
	if(!get_colors_(store , list->head_f))
	{
		free_tptr(store->textures , 4);
		free_list(list);
		free(store);
		return NULL;
	}
	store->map = get_map(list->head_s);
	if(store->map == NULL)
	{
		free_tptr(store->textures , 4);
		free_list(list);
		free(store);
		return NULL;
	}
	free_list(list);
	if(!parse_map(store->map))
	{
		free_tptr(store->textures , 4);
		free_dptr(store->map);
		free(store);
		return NULL;
	}
	int map_w = 0;
	int map_h = 0; 
	char **map = store->map;
	map_w = ft_strlen(map[0]);
	while(map[map_h])
		map_h++;
	store->map_h  = map_h;
	store->map_w = map_w ;
	// calculate the tile before working 
	int tile_width = W_WIN / map_w ;
	int tile_height = H_WIN / map_h ;
	store->tile  = (tile_height < tile_width) ? tile_height : tile_width;
	if(store->tile < 1)
		store->tile = 1; 
	for(int i = 0 ; map[i]   ; i++)
	{
		bool find = false;
		for(int j = 0 ; map[i][j]; j++)
		{
			if(is_player(map[i][j]))
			{
				store->player_x = j * store->tile + store->tile / 2;
				// to get i and j just a small thing is to / j   = (store->>player_x - (store->tile /2)) / store->tile
				store->player_y = i * store->tile + store->tile /2 ;
				find  = true;
				break;
			}
			if(find == true)
				break;
		}
	}
	printf("x  = %d, y = %d , h = %d , w =  %d\n\n" , store->player_x , store->player_y , store->map_h , store->map_w);
	print_cub3d(store);
	return store;
}
