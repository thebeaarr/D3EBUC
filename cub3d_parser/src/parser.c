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
  /// check the path and open it to see if it's just good ? 
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
  printf("x  = %d, y = %d" , store->player_x , store->player_y);
  print_cub3d(store);
  return store;
}
