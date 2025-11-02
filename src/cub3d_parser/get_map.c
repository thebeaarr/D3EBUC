#include "../../cub3d.h" 

char **get_map(t_file *head)
{
  t_file *current = head;
  int max = 0;

  int i = 0;
  while(current)
  {
	if((int)ft_strlen(current->line) > max)
		max = ft_strlen(current->line);
	current =  current->next;
	i++;
  }
  char **map = malloc(sizeof(char *) * ( i + 1));
  map[i] = NULL;
  current = head;
   i = 0;
  while(current)
  {
    // map[i] = strdup(current->line);
	int j  =0;
	map[i] = malloc(sizeof(char ) * ( max + 1));

	while(current->line[j])
	{
		map[i][j] = current->line[j];
		j++;
	}
	while(j < max)
		map[i][j++] = ' ';
	map[i][j] = '\0'; 
    current = current->next;
    i++;
  }
  return map;
}

