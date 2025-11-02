#include "../../cub3d.h" 

t_list *read_file(char *path)
{
  char *tmp ;
  t_list *list = NULL;
  t_file *line = NULL;
  int fd = open(path  , O_RDONLY);
  if(fd < 0)
  {
    printf("ERROR: failed to open file");
    return NULL;
  }
    // read first part of the map
  while((tmp = get_next_line(fd)))
  {
    int i = 0;
    if(tmp[0] == '\n' || isspaces(tmp))
    {
      free(tmp);
      continue;
    }
    while(tmp[i] == '1' || tmp[i] == 32 || tmp[i] == '\n')
      i++;
    if(tmp[i] == '\0')
		break;
    i = 0;
    while(isspace(tmp[i]))
      i++;

    line = anode(tmp + i);
    if(!list)
    {
      list = malloc(sizeof(t_list)); 
	  // because of the move or jump depends on
	  // uninitialised variables !!! find a good soltuions
	  list->head_f = NULL;
	  list->head_s = NULL;
      list->head_f = line  ;
    }
    else
      add_back(&list->head_f , line);
	free(tmp);
  }
  if(size_list(list->head_f) > 6)
  {
	free_list(list);
	return NULL;
  }
  // read first part of the map
  if(tmp == NULL)
  {
	// remove shit and freee
	printf("uncompete map\n");
	free_list(list);
	exit(1);
  }
  list->head_s = anode(tmp);
  free(tmp);
  while((tmp = get_next_line(fd)))
  {
    line = anode(tmp);
    add_back(&list->head_s , line);
	free(tmp);
  }
  if(tmp)
  	free(tmp);
  close(fd);  
  return list;
}
