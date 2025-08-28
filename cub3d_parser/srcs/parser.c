#include "../include/parser.h"
#include <stdbool.h>
// make a node with line and NULL in the next;

t_file *anode(char *line)
{
  t_file *node = malloc(sizeof(t_file));
  node->line = line;
  node->next = NULL;
  return node;
}
void add_back(t_list *head, t_file *current)
{
  t_file *tmp;
  tmp = head->head;
  while(tmp->next)
    tmp = tmp->next;
  tmp->next = current;
} 

bool strings_cal(char ***txt)
{
  char **w;
  int i = 0;
  while (txt[i])
  {
    w = txt[i];
    int count = 0;
    while(w[count])
    {
      count++;
    }
    if(count != 2)
      return false;
    i++;
  }
  return true;
}
char ***get_textures(t_list *lst)
{
  char ***txt;
  int count = 0;
  t_file *tmp = lst->head;
  while (tmp)
  {
    if(strncmp(tmp->line , "EA" , 2) == 0 || 
        strncmp(tmp->line , "SO" , 2 ) == 0||
        strncmp(tmp->line , "NO" , 2 ) == 0||
        strncmp(tmp->line , "WE" , 2 ) == 0)
    {
      count++;
    }
    else if(tmp->line[0] == '\n')
    {
      tmp = tmp->next;
      continue;
  
    }
    else
      break;
    tmp = tmp->next;
  }
  if(count != 4)
    return NULL;
  txt = malloc(sizeof(char **) * 4);
  count = 0;
  tmp = lst->head;
  while (tmp)
  {
    if(strncmp(tmp->line , "EA" , 2) == 0 || 
        strncmp(tmp->line , "SO" , 2 ) == 0||
        strncmp(tmp->line , "NO" , 2 ) == 0||
        strncmp(tmp->line , "WE" , 2 ) == 0)
    {
      txt[count] = ft_split(tmp->line, 32);
      count++;
    }
    else if(tmp->line[0] == '\n')
    {
      tmp = tmp->next;
      continue;
    }
    else
      break;
    tmp = tmp->next;
  }
  if(count != 4)
    return NULL;
  if(!strings_cal(txt))
    return NULL;
  lst->ptr_hold = tmp; // current place when we got to take the colors  i guess ( if they eexist )
  return txt;
}

int get_color(char *file )
{
  char **color = ft_split(file, ',');
  int count = 0;
  while(color[count])
    count++;
  if(count != 3)
    return -1;
  int r = ft_atoi(color[0]);
  int g = ft_atoi(color[1]);
  int b = ft_atoi(color[2]);
  if(r  == -1 || g == -1  || b == -1)
    return -1;
  int rgb = (r << 16) | (g << 8) | b;
  return rgb;
}

int *get_fc(t_list *lst)
{
  t_file *head = lst->ptr_hold;
  int *tab = malloc(sizeof(int) * 2);
  int count = 0;
  while (head)
  {
    if(head->line[0] == 'F')
    {
      *tab = get_color(head->line);
      if(*tab == -1)
        return NULL;
      count++;
    }
    else if(head->line[0] == 'C')
    {
      *(tab + 1) = get_color(head->line);
      if(*(tab + 1) == -1)
        return NULL;
      count++;
    }
    else if(head->line[0] != '\n' )
      break;
    head = head->next;
  }
  if(count != 2)
    return NULL;
  lst->ptr_hold = head;
  return tab;
}
char **get_map(t_list *lst)
{
  t_file *clc;
  clc = lst->ptr_hold;
  int calcu;
  calcu = 0;
  while(clc)
  {
    calcu++;
    clc = clc->next;
  }
  char **map = malloc(sizeof(char *) * (calcu + 1));
  t_file *copy = lst->ptr_hold;
  int size = 0;
  while (copy)
  {
    map[size] = ft_strdup(copy->line);
    size++;
    copy = copy->next;
  }
  map[size] = NULL;
  return map;
}
bool textures_valid_exit(char ***textures)
{
  char ***txts = textures; // keep the adress or not just go fuck ur self in a ram ( that's what can i say today )

  const int index = 0;
  for (int i = 0;txts[i]; i++)
  {
      int d = open(txts[i][index], O_RDONLY);
      if(d < 0)
      {
        printf("no exist ??? ");
        return false;
      }
      close(d);
  }
  return true;
}

bool valid_cub_file(t_cub3d *cub3d)
{
  // check if the textures path are exit or not
  printf("hna fin ghadya t segv\n");
  char ***textures = cub3d->textures;
  if(!textures_valid_exit(textures)) // valid path + exist
  {
    printf("ERROR:\n");
    return false;
  }
  // char **map = cub3d->map;
  // if(!valid_map(map))
  // {
  //   printf("ERROR:\n");
  //   return false;
  // }
  printf("already segv\n");
  return true;
}
t_cub3d *main_parser(char *file)
{
  // just  open and read on the file. 
  // trying to understand how does this gonna behave at the end
  int fd = open(file, O_RDONLY);
  t_list *lst;
  int srgt = 0;
  t_file *current;
  lst = NULL;
  current = NULL;
  char *tmp = NULL;
  while((tmp = get_next_line(fd)))
  {
    if(tmp)
    current = anode(tmp);
    if(!lst)
    {
      lst = malloc(sizeof(t_list));
      lst->head = current;
    }
    else
    add_back(lst, current);
    printf("%s", current->line);
  }
  printf("seg %d ???\n\n " , srgt++);
  char ***txt;
  txt = get_textures(lst);
  printf("seg %d ???\n\n " , srgt++);

  int *tab = get_fc(lst);
  printf("seg %d ???\n\n " , srgt++);
  printf("%d , %d\n", tab[0], tab[1]);
  
  char **map = get_map(lst);
  printf("seg %d ???\n\n " , srgt++);

  if(txt == NULL || tab == NULL || map == NULL)
  {
    if(!txt)
    printf("txt");
    if(!tab)
      printf("tab");
    if(map == NULL)
    printf("moerim");
    printf("ERROR:\n");
    return NULL;
  }
  printf("seg %d ???\n\n " , srgt++);
  t_cub3d *cub3d;
  cub3d = malloc(sizeof(t_cub3d));
  
  cub3d->textures = txt;
  cub3d->colors = tab;
  cub3d->map = map;

  if(!valid_cub_file(cub3d))
  {
    printf("ERROR:\n");
    return NULL;
  }
  printf("seg %d ???\n\n " , srgt++);
  printf("%d", cub3d->colors[0]);
  printf("seg %d ???\n\n ", srgt++);
  return cub3d;
}
