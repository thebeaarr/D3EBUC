#include "../include/parser.h"

int size_list(t_file *head)
{
  t_file *current = head;
  int size=0;
  while(current)
  {
    size++;
    current = current->next;
  }
  return size;
}

void print_cub3d(t_cub3d *cub3d)
{
  char ***txt = cub3d->textures;
  for(int i = 0 ; txt[i] ; i++)
  {
    for(int j =0; txt[i][j];j++)
      printf("%s", txt[i][j]);
    printf("\n");
  }
  printf("floor = %d\nceiling = %d\n", cub3d->floor, cub3d->ceiling); // already the map is just checked incease of the overflow
  char **map ;
  map = cub3d->map;
  for(int i = 0 ; map[i] ; i++)
    printf("--%s|\n" , map[i]);// call a function that check if we have one
}

bool is_player(char c)
{
  return c == 'N' || c == 'W' || c == 'E' || c == 'S' ;
}


void free_file(t_file*head)
{
	t_file *tmp ;
	tmp = NULL;
	
	while(head)
	{
		tmp = head->next ;
		free(head->line);
		free(head);
		head = tmp ;
	}
}
void free_list(t_list *head)
{
	if(head)
	{
		free_file(head->head_f);
		free_file(head->head_s);
		free(head);
	}
}

