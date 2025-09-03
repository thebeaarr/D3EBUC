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
  int size = size_list(list->head_f);
  if(size > 6)
    return NULL;
  store->textures = get_textures(list->head_f);
  if(store->textures == NULL)
    return NULL;
  if(!get_colors_(store , list->head_f))
    return NULL;
  store->map = get_map(list->head_s);
  if(store->map == NULL)
    return NULL;
  if(!parse_map(store->map))
    return NULL;
//   print_cub3d(store);
  return store;
}
