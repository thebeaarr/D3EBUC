#include "../include/parser.h"

bool dup_c(t_file *head)
{
  t_file *current ;
  current= head;
  int count_f = 0;
  int count_c = 0;
  while(current)
  {
    char *tmp  = current->line;
    int index = 0;
    while(isspace(tmp[index]))
      index++;
    if(!strncmp("F" , tmp + index , 1) && isspace(tmp[index + 1]))
      count_f++;
    else if(!strncmp("C" , tmp + index , 1) && isspace(tmp[index + 1]))
      count_c++;
    if(count_f > 1 || count_c > 1)
      return true;
    current = current->next;
  }
  return (count_f != 1 || count_c != 1);
}

char *rm_spaces_check(char *s)
{
  char *new = malloc(sizeof(char) * ft_strlen(s) + 1);
  int index = 0;
  int t = 0;
  
  if(s[0] == 'C' || s[0] == 'F')
    index = 1;
  
  while(s[index] && isspace(s[index]))
    index++;
  
  while(s[index])
  {
      new[t] = s[index];
      t++;
    index++;
  }
  new[t] = '\0';
  return new;
}

int get_color(char *s )
{
  if (!s)
    return -1;
  
  char *str = rm_spaces_check(s);
  if (!str)
    return -1;
    
  char **color = ft_split(str, ',');
  free(str);
  if (!color)
    return -1;
    
  int count = 0;
  while(color[count])
    count++;
    
  if(count != 3)
  {
    for(int i = 0; i < count; i++)
      free(color[i]);
    free(color);
    return -1;
  }
  
  int r = ft_atoi(color[0]);
  int g = ft_atoi(color[1]);
  int b = ft_atoi(color[2]);
  
  // Free memory after use
  for(int i = 0; i < count; i++)
    free(color[i]);
  free(color);
  if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    return -1;
    
  int rgb = (r << 16) | (g << 8) | b;
  return rgb;
}

bool get_colors_(t_cub3d *store , t_file *head)
{
  t_file *current = head;
  if(dup_c(head))
  {
    printf("ERROR:duplicated colors\n" );
    return false;
  }
  store->ceiling = -1;
  store->floor = -1;
  while(current)
  {
    char *tmp  = current->line;
    int index = 0;
    while(isspace(tmp[index]))
      index++;
    if(!strncmp("F" , tmp + index , 1) && isspace(tmp[index + 1]))
      store->floor = get_color(tmp + index);
    else if(!strncmp("C" , tmp + index , 1) && isspace(tmp[index + 1]))
      store->ceiling = get_color(tmp + index);
    current = current->next;
  }
  if(store->ceiling == -1  || store->floor == -1)
  {
    printf("ERROR: Invalid color values\n");
    return false;
  }
  return true;
}
