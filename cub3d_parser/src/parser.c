#include "../include/parser.h"

t_cub3d *get_file_as_struct(char *path)
{
  t_cub3d *store;
  store = NULL;
  store = malloc(sizeof(t_cub3d));
  t_list *list = read_file(path);
  if(list == NULL)
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
//   print_cub3d(store);
  return store;
}
