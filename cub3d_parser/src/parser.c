#include "../include/parser.h"
#include <stdbool.h>


// split with spaces

static int is_whitespace(char ch)
{
  return (ch == 32 || (ch >= 9 && ch <= 13));
}

static size_t ft_countword(const char *str)
{
  int in_word = 0;
  size_t count = 0;
  while (*str)
  {
    if (!is_whitespace(*str) && !in_word)
    {
      in_word = 1;
      count++;
    }
    else if (is_whitespace(*str))
      in_word = 0;
    str++;
  }
  return count;
}

static size_t calculate_every_word(const char *s)
{
  size_t len = 0;
  while (s[len] && !is_whitespace(s[len]))
    len++;
  return len;
}

static void	free_memory(char **trunks, size_t i)
{
	while (i--)
		free(trunks[i]);
}

static int split_helper(char **trunks, const char *s)
{
  size_t i = 0;
  size_t word_len;
  while (*s)
  {
    if (!is_whitespace(*s))
    {
      word_len = calculate_every_word(s);
      trunks[i] = (char *)malloc((word_len + 1) * sizeof(char));
      if (!trunks[i])
      {
        free_memory(trunks, i);
        return 0;
      }
      ft_strlcpy(trunks[i], s, word_len + 1);
      s += word_len;
      i++;
    }
    else
      s++;
  }
  return 1;
}

char **ft_split2(char *s)
{
  size_t word_count;
  char **trunks;
  if (s == NULL)
    return NULL;
  while(is_whitespace(*s))
    s++;
  word_count = ft_countword(s);
  trunks = malloc((word_count + 1) * sizeof(char *));
  if (!trunks)
    return NULL;
  trunks[word_count] = NULL;
  if (!split_helper(trunks, s))
  {
    free(trunks);
    return NULL;
  }
  return trunks;
}

// spaces 
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
      txt[count] = ft_split2 (tmp->line);
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
#include<stdio.h>
void print_cub3d(t_cub3d *cub3d)
{
  char ***txt = cub3d->textures;
  for(int i = 0 ; txt[i] ; i++)
  {
    for(int j =0; txt[i][j];j++)
    {
      printf("%s", txt[i][j]);
      // we have to check if the path is true one , open and close the file text to see if it existed.
    }
    printf("\n");
  }
  printf("floor = %d\nceiling = %d\n", cub3d->colors[0] , cub3d->colors[1]); // already the map is just checked incease of the overflow
  char **map ;
  map = cub3d->map;
  for(int i = 0 ; map[i] ; i++)
    printf("map[%d] = %s" , i + 1, map[i]);// call a function that check if we have one
    // player ( just one with the sings ( E , W , S , N ))
    // the map is closed ( 1 ),
    // the map contains just 1 , 0 , or spaces , or just
}
bool textures_valid(char ***textures_v)
{
  char ***textures = textures_v;
  for(int i = 0 ; textures[i] ; i++)
  {
    // char*clean_path = ft_substr(textures[i][1] , 0 , ft_strlen(textures[i][1]) -1 );
    // free(textures[i][1]);
    // textures[i][1] = clean_path ;
    char *extension = ft_strrchr(textures[i][1] , '.');
    if(strcmp(extension, ".xpm"))
    {
      printf("ERROR:no extension xpm in the textures\n");
      return false;
    }
    int fd = open(textures[i][1] , O_RDONLY);
    if(fd < 0)
    {
      printf("ERROR:textures file of %s not existed\n", textures[i][0]) ;
      close(fd);
      return false;
    }
    close(fd);
  }
  return true;
}
bool map_valid(char **map_v)
{
  char **map = map_v;
  (void)map;
  return true;
}
t_cub3d *main_parser(char *file)
{
  int fd = open(file, O_RDONLY);
  t_list *lst;
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
  }
  close(fd);
  char ***txt;
  txt = get_textures(lst);
  int *tab = get_fc(lst);
  char **map = get_map(lst);
  if(txt == NULL || tab == NULL || map == NULL)
  {
    if(!txt)
      printf("txt");
    if(!tab)
      printf("tab");
    if(map == NULL)
      printf("map");
    return NULL;
  }
  t_cub3d *cub3d;
  cub3d = malloc(sizeof(t_cub3d));
  cub3d->textures = txt;
  cub3d->colors = tab;
  cub3d->map = map;
  // print_cub3d(cub3d);
  // map_valid()
  // textures opened and closed ?

  if(!textures_valid(cub3d->textures))
  {
    printf("ERROR:map not valid\n");
    return NULL;
  }

  return cub3d;
}
