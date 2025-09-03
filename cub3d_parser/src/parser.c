#include "../include/parser.h"
#include <ctype.h>
#include <ctype.h>
#include <ctype.h>
#include <stdbool.h>


static size_t	ft_countword(const char *str)
{
	int		in_word;
	size_t	count;

	in_word = 0;
	count = 0;
	while (*str)
	{
		if (!isspace(*str) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (isspace(*str))
			in_word = 0;
		str++;
	}
	return (count);
}

static size_t	calculate_every_word(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && !isspace(s[len]))
		len++;
	return (len);
}

static void	free_memory(char **trunks, size_t i)
{
	while (i--)
		free(trunks[i]);
}

static int	split_helper(char **trunks, const char *s)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		if (!isspace(*s))
		{
			word_len = calculate_every_word(s);
			trunks[i] = (char *)malloc((word_len + 1) * sizeof(char));
			if (!trunks[i])
			{
				free_memory(trunks, i);
				return (0);
			}
			ft_strlcpy(trunks[i], s, word_len + 1);
			s += word_len;
			i++;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split_space(const char *s)
{
	size_t	word_count;
	char	**trunks;

	if (s == NULL)
		return (NULL);
	word_count = ft_countword(s);
	trunks = malloc((word_count + 1) * sizeof(char *));
	if (!trunks)
		return (NULL);
	trunks[word_count] = NULL;
	if (!split_helper(trunks, s))
	{
		free(trunks);
		return (NULL);
	}
	return (trunks);
}

#include "../include/parser.h"
t_file *anode(char *line)
{
  t_file *node = malloc(sizeof(t_file));
  node->line = strdup(line);
  node->next = NULL;
  return node;
}

void add_back(t_file **head, t_file *current)
{
  t_file *tmp;
  tmp = *head;
  while(tmp->next)
    tmp = tmp->next;
  tmp->next = current;
}
// bool is_first_str_map(char *str)
// {
//   int i = 0;
//   while(str[i])
//   {
//     if(str[i] != '1' ||  !isspace(str[i]) || str[i] != '\n')
//       return false;
//     i++;
//   }
//   return true;
// }
bool isspaces(char *line)
{
  int i = 0;
  while(line[i])
  {
    if(!isspace(line[i]))
      return false;
    i++;
  }
  return line[i] == '\0';
}

#include <ctype.h>
t_list *read_file(char *path)
{
  char *tmp ;
  t_list *list = NULL;
  t_file *line ;
  int fd = open(path  , O_RDONLY);
  if(fd < 0)
  {
    printf("ERROR: failed to open file");
    exit(1);
  }
    // read first part of the map
  while((tmp = get_next_line(fd)))
  {
    int i = 0;
    if(tmp[0] == '\n')
    {
      free(tmp);
      continue;
    }
    while(tmp[i] == '1' || isspace(tmp[i]) || tmp[i] == '\n')
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
      list->head_f = line  ;
    }
    else
      add_back(&list->head_f , line);
  }
  // read first part of the map
  list->head_s = anode(tmp);
  while((tmp = get_next_line(fd)))
  {
    line = anode(tmp);
    add_back(&list->head_s , line);
  }
  close(fd);  
  return list;
}

int is_txt(char *line)
{
  if(!ft_strncmp(line , "NO" , 2) && isspace(line[2]))
    return 1;
  if(!ft_strncmp(line , "SO" , 2) && isspace(line[2]))
    return 2;
  if(!ft_strncmp(line , "WE" , 2) && isspace(line[2]))
    return 3;
  if(!ft_strncmp(line , "EA" , 2) && isspace(line[2]))
    return 4;
  return 0;
}

bool dup_(t_file *ca)
{
  int w = 0;
  int e = 0;
  int s =0;
  int n = 0;
  int check =0;
  t_file * c = ca;
  while(c)
  {
    check = is_txt(c->line);
    if(check == 1)
      n++;
    else if(check == 2)
      s++;
    else if(check == 3)
      w++;
    else if(check == 4)
      e++;
    if(e > 1 || w > 1 || s > 1 || n > 1)
      return true;
    c = c->next;
  }
  return !(e == 1 && w == 1 && s == 1 && n == 1);
}
bool check_ntxt(char **str)
{
  int i = 0;
  while(str[i])
    i++;
  if(i > 2)
    return false;
  return true;  
}

bool path_valid(char *str)
{
  char *extension = strrchr(str,'.');
  if(!extension || strcmp(extension  , ".xpm") != 0)
  {
    printf("extension path .xpm\n");
    return false;
  }
  int fd = open(str , O_RDONLY);
  if(fd < 0)
  {
    printf("file cannot be open\n");
    return false;
  }
  close(fd);
  return true;
}

char ***get_textures(t_file *head)
{
  t_file *current = head;
  // check if texutres enough and not dups;
  if(dup_(current))
  {
    printf("duplicated textures/not enough texutre!");
    return NULL;
  }
  char ***textures = malloc(sizeof(char **) * 5);
  textures[4] = NULL;
  int count  = 0;
  while(current && count < 4)
  {
    if(is_txt(current->line))
    {
      textures[count] = ft_split_space(current->line);
      if(!check_ntxt(textures[count]) || !path_valid(textures[count][1]))
      {
        printf("invalid textures");
        return NULL;
      }
      count++;
    }
    current = current->next;
  }
  return textures;
}

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
    map[i] = current->line;
    current = current->next;
    i++;
  }
  return map;
}

void print_list(t_file *head)
{
  t_file *current= head;
  while(current)
  {
    printf("%s" , current->line);
    current = current->next;
  }
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
    printf("map[%d] = %s" , i + 1, map[i]);// call a function that check if we have one
}

bool is_player(char c)
{
  return c == 'N' || c == 'W' || c == 'E' || c == 'S' ;
}


bool map_closed(char **map)
{
	int i  = 1;
	for( ; map[i +1] ; i++)
	{
		for(int j = 0 ; map[i][j] ; j++)
		{
			if(isspace(map[i][j]))
			{
				if((map[i - 1][j] == '0' || map[i + 1][j] == '0' || map[i][j+1] == '0' || map[i][j - 1] == '0' ) && j > 0 )
					return false;
			}
			if(map[i][j] == '0' || is_player(map[i][j]))
			{
			  if((isspace(map[i-1][j]) || isspace(map[i + 1][j]) || isspace(map[i][j+1]) || isspace(map[i][j - 1]) ) && j > 0 )
			    return false;
			}
		}
	}
	for(int j = 0; map[i][j] ; j++)
	{
		if(is_player(map[i][j]) || map[i][j] == '0' )
			return false;
	}
	
	return true;
}

bool parse_map(char **map)
{	
	int count_p  =0;
	for(int i = 0; map[i] ;i++)
	{
		for(int k =0 ; map[i][k];k++)
		{
		  if(is_player(map[i][k]))
		    count_p++;
		}
	}
	if(count_p != 1)
	{
		printf("ERROR:player not exist or there is multiple player\n");
		return false;
	}
	for(int i = 0 ; map[i] ; i++)
	{
		if(map[i][0] == '\n')
		{
		  printf("empty line\n");
		  return false;
		}
		int j = 0;
		for(; map[i][j] ; j++)
		{
		  if(map[i][j] != '1' && map[i][j] != '0' && !is_player(map[i][j]) && !isspace(map[i][j]))
		  {
		    printf("not a valid char\n");
		    return false;
		  }
		  if(!isspace(map[i][j]))
		    break;
		}
		if(map[i][j] == '\0' || map[i][j] == '\n')
		{
			printf("no walls\n");
			return false;
		}
		if(!map_closed(map))
			return false;
	}
	return true;
}	

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
//   printf("----------- first list\n");
//   print_list(list->head_f);
//   printf("------------second list\n");
//   print_list(list->head_s);
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
