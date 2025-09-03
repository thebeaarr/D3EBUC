#include "../include/parser.h"

char **get_map(t_file *head)
{
  t_file *current = head;
  // char *tmp ;
  int i = 0;
  while(current)
  {
    i++;
    current =  current->next;
  }
  char **map = malloc(sizeof(char *) * ( i + 1));
  map[i] = NULL;
  current = head;
   i = 0;
  while(current)
  {
    map[i] = strdup(current->line);
    current = current->next;
    i++;
  }
  return map;
}

