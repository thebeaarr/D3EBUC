#include "../include/parser.h"
#include <stdbool.h>
// // split with spaces

// // spaces 
// // make a node with line and NULL in the next;

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

// bool strings_cal(char ***txt)
// {
//   char **w;
//   int i = 0;
//   while (txt[i])
//   {
//     w = txt[i];
//     int count = 0;
//     while(w[count])
//     {
//       count++;
//     }
//     if(count != 2)
//       return false;
//     i++;
//   }
//   return true;
// }

// char ***get_textures(t_list *lst)
// {
//   char ***txt;
//   int count = 0;
//   t_file *tmp = lst->head;
//   while (tmp)
//   {
//     if(strncmp(tmp->line , "EA" , 2) == 0 ||
//         strncmp(tmp->line , "SO" , 2 ) == 0||
//         strncmp(tmp->line , "NO" , 2 ) == 0||
//         strncmp(tmp->line , "WE" , 2 ) == 0)
//     {
//       count++;
//     }
//     else
//       break;
//     tmp = tmp->next;
//   }
//   if(count != 4)
//     return NULL;
//   txt = malloc(sizeof(char **) * 4);
//   count = 0;
//   tmp = lst->head;
//   while (tmp)
//   {
//     if(strncmp(tmp->line , "EA" , 2) == 0 ||
//         strncmp(tmp->line , "SO" , 2 ) == 0||
//         strncmp(tmp->line , "NO" , 2 ) == 0||
//         strncmp(tmp->line , "WE" , 2 ) == 0)
//     {
//       txt[count] = ft_split(tmp->line , 32);
//       count++;
//     }
//     else if(tmp->line[0] == '\n')
//     {
//       tmp = tmp->next;
//       continue;
//     }
//     else
//       break;
//     tmp = tmp->next;
//   }
//   if(count != 4)
//     return NULL;
//   if(!strings_cal(txt))
//     return NULL;
//   lst->ptr_hold = tmp; // current place when we got to take the colors  i guess ( if they eexist )
//   return txt;
// }
#include <ctype.h>
char *rm_spaces_check(char *s)
{
  char *new = malloc(sizeof(char) * ft_strlen(s) + 1);
  int index = 0;
  int t = 0;
  
  // Skip the initial 'C' or 'F' character and any following spaces
  if(s[0] == 'C' || s[0] == 'F')
    index = 1;
  
  while(s[index] && isspace(s[index]))
    index++;
  
  while(s[index])
  {
    if(!isspace(s[index]))
    {
      new[t] = s[index];
      t++;
    }
    index++;
  }
  new[t] = '\0';  // Null terminate the string

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
  free(str);  // Free the processed string
  
  if (!color)
    return -1;
    
  int count = 0;
  while(color[count])
    count++;
    
  if(count != 3)
  {
    // Free memory before returning
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

// int *get_fc(t_list *lst)
//   t_file *head = lst->head;
//   int *tab = malloc(sizeof(int) * 2);
//   int count = 0;
// {
//   while (head)
//   {
//     if(head->line[0] == 'F')
//     {
//       *tab = get_color(head->line);
//       if(*tab == -1)
//         return NULL;
//       count++;
//     }
//     else if(head->line[0] == 'C')
//     {
//       *(tab + 1) = get_color(head->line);
//       if(*(tab + 1) == -1)
//         return NULL;
//       count++;
//     }
//     else if(head->line[0] != '\n' )
//       break;
//     head = head->next;
//   }
//   if(count != 2)
//     return NULL;
//   return tab;
// }
// char **get_map(t_list *lst)
// {
//   t_file *clc =lst->head;
//   int calcu;
//   calcu = 0;
//   t_file *gotten  = lst->head;
//   int s  = 6;
//   while(s)
//   {
//     gotten = gotten->next;
//     s--;
//   }
  
//   clc = gotten;
//   while(clc)
//   {
//     calcu++;
//     clc = clc->next;
//   }
//   char **map = malloc(sizeof(char *) * (calcu + 1));
//   t_file *copy = gotten;
//   int size = 0;
//   while (copy)
//   {
//     map[size] = ft_strdup(copy->line);
//     size++;
//     copy = copy->next;
//   }
//   map[size] = NULL;
//   return map;
// }
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
  printf("C = %d\nF = %d\n", cub3d->ceiling , cub3d->floor); // already the map is just checked incease of the overflow
  char **map ;
  map = cub3d->map;
  for(int i = 0 ; map[i] ; i++)
    printf("map[%d] = %s" , i + 1, map[i]);// call a function that check if we have one
    // player ( just one with the sings ( E , W , S , N ))
    // the map is closed ( 1 ),
    // the map contains just 1 , 0 , or spaces , or just
}


#include "../include/parser.h"

#include <ctype.h>
#include <ctype.h>

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
      printf("%s\n",s);
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

int isspaces(char *str)
{
  int index =0 ;
  while(isspace(str[index]))
    index++;
  return str[index] == 0;
}

int is_part_map(char c)
{
   if(c == 'N' || c == 'E' || c == 'F' || c == 'C' || c == 'W' || c == 'S')
    return 1;
  else
    return 0;
}

char *clean_(char *line)
{
  char *clean;
  int index = 0;
  int size = strlen(line);
  
  // Skip leading spaces
  while(isspace(line[index]))
    index++;
    
  if(is_part_map(line[index]) == 0)
    return line;
    
  // Find the end of the line (before trailing newline/spaces)
  while(size > 0 && (line[size-1] == '\n' || isspace(line[size-1])))
    size--;
    
  clean = ft_substr(line, index, size - index);
  free(line);
  return clean; 
}

t_list *read_file(char *file )
{
  int fd = open(file, O_RDONLY);
  if (fd < 0)
  {
    printf("ERROR: Cannot open file %s\n", file);
    return NULL;
  }
  
  t_list *lst;
  t_file *current;
  lst = NULL;
  current = NULL;
  char *tmp = NULL;
  
  while((tmp = get_next_line(fd)))
  {
    if(isspaces(tmp))
    {
      free(tmp);
      continue;
    }
    tmp = clean_(tmp);
    if(tmp == NULL)
    {
      close(fd);
      return NULL;
    }
    current = anode(tmp);
    if(!lst)
    {
      lst = malloc(sizeof(t_list));
      if (!lst)
      {
        close(fd);
        return NULL;
      }
      lst->head = current;
    }
    else
    {
      add_back(lst, current);
    }
  }
  close(fd);
  return lst;
}

int is_txt(char *line)
{
  return  (!ft_strncmp(line , "NO" , 2) && isspace(line[2])) || 
          (!ft_strncmp(line , "SO" , 2) && isspace(line[2])) || 
          (!ft_strncmp(line , "WE" , 2) && isspace(line[2])) || 
          (!ft_strncmp(line , "EA" , 2) && isspace(line[2]));
}

bool dup_txt(t_list *lst)
{
  int n =0;
  int e = 0;
  int w = 0;
  int s=0;
  t_file *current = lst->head;
  while(current)
  {
    if(strncmp(current->line , "NO" , 2) == 0)
      n++;
    else if(strncmp(current->line , "SO" , 2) == 0)
      s++;
    else if(strncmp(current->line , "WE" , 2) == 0)
      w++;
    else if(strncmp(current->line , "EA" , 2) == 0)
      e++;
    if(e > 1 || w > 1 || s > 1 || n > 1)
    {
      printf("ERROR:duplicate textures\n");
      return true;
    }
    current = current->next;
  }
  return false;

}
char ***get_textures(t_list *lst)
{
  t_file *tmp ; 
  tmp = lst->head;
  char ***ret = malloc(sizeof(char **) * 5);
  ret[4] = NULL;
  int ind = 0;
  if(dup_txt(lst))
    return NULL;
  while(tmp && ind < 4)  // Continue until we find all 4 textures
  {
    if(is_txt(tmp->line))
    {
      int i =0;
      ret[ind] = ft_split_space(tmp->line);
      for( ; ret[ind][i] ; i++)
      {
        printf("%s\n" , ret[ind][i]);
      }
      if(i != 2)
      {
        printf("ERROR: Texture line must have exactly 2 parts (identifier and path)\n");
        return NULL;
      }
      if (!ret[ind] || !ret[ind][0] || !ret[ind][1])
      {
        printf("ERROR: Invalid texture line format\n");
        // Free allocated memory before returning
        for(int j = 0; j < ind; j++)
        {
          if(ret[j])
          {
            for(int k = 0; ret[j][k]; k++)
              free(ret[j][k]);
            free(ret[j]);
          }
        }
        free(ret);
        return NULL;
      }
      ind++;
    }
    tmp = tmp->next;
  }

  if(ind != 4)
  {
    printf("ERROR: Must have exactly 4 texture identifiers (NO, SO, WE, EA)\n");
    return NULL;
  }
  //check numebr of string ? 
  
  // path validation - check extension
  for(int i  = 0 ; ret[i] ; i++)
  {
    char *extension = strrchr(ret[i][1] , '.');
    if(!extension || strcmp(extension , ".xpm") != 0)
    {
      printf("ERROR: Invalid path extension, must be .xpm\n");
      exit(1);
    }
  }

  // existence 
  for(int i = 0 ; ret[i] ; i++)
  {
    if (!ret[i][1])
    {
      printf("ERROR: Missing texture path\n");
      return NULL;
    }
    int fd = open(ret[i][1] , O_RDONLY);
    if(fd < 0)
    {
      printf("ERROR:path %s not exist\n", ret[i][1]);
      exit(1);
    }
    close(fd);
  }
  printf("succuss\n");
  return ret ;
}

void colors_(t_list *lst , t_cub3d *cub3d )
{
  t_file *tmp ;
  int ind = 0;
  tmp = lst->head;
  while(tmp && ind < 2)  // Continue until we find both colors
  {
    if(strncmp(tmp->line , "F" , 1) == 0)
    {
      cub3d->floor = get_color(tmp->line);  // Skip "F " prefix
      if(cub3d->floor == -1)
      {
        printf("ERROR:problem\n");
        exit(1);  
      }
      ind++;
    }
    else if(strncmp(tmp->line , "C" , 1) == 0)
    {
      cub3d->ceiling = get_color(tmp->line);  // Skip "C " prefix
      if(cub3d->ceiling == -1)
      {
        printf("ERROR:problem\n");
        exit(1);
      }
      ind++;
    }
    tmp = tmp->next;
  }
  printf("%d\n" , ind);
  if(ind != 2)
  {
    printf("ERROR: Floor and ceiling colors are missing or incomplete!\n");
    exit(1);
  }
}

char **map_(t_list *lst)
{
  t_file *tmp ;
  tmp = lst->head;
  int count = 6;
  while(tmp && count)
  {
    tmp = tmp->next;
    count--;
  }
  char **map;
  int c_s  = 0;
  t_file *h = tmp;
  while(tmp)
  {
    c_s++;
    tmp = tmp->next;
  }
  map = malloc(sizeof(char *) * (c_s + 1));
  map[c_s] = NULL;
  int i =0;
  while(h && i < c_s)
  {
    map[i] = ft_strdup(h->line);
    h = h->next ;
    i++; 
  }
  // valid this map , check for any char unlike W , E , S , N ( this happen only one at one time for the player) , 1 and 0 
  // check again for the player with the number of 1 only check for the map if it just closed ,
  // we are done with the parsing
  // started with checking valid content ?
  // int count_p = 0;
  // for(int i = 0 ; map[i]; i++)
  // {
  //   for(int j = 0; map[i][j];j++)
  //   {
  //     if( map[i][j] == 'W' || map[i][j] == 'E'|| map[i][j] == 'N'|| map[i][j] == 'S')
  //       count_p++;
  //     if(count_p > 1)
  //     {
  //       printf("ERROR:duplicated players\n");
  //       exit(1);
  //     }
  //     if(map[i][j] && !(map[i][j] == '0' || map[i][j] == '1' || map[i][j] == 'W' || map[i][j] == 'E'||map[i][j] == 'S'||map[i][j] == 'N'||map[i][j] == ' '))
  //     {
  //       printf("ERROR:invalid char\n");
  //       exit(1);
  //     }
  //   }
  // }
  int count_p = 0;
  for(int i = 0 ; map[i] ; i++)
  {
    for(int j = 0 ; map[i][j] ; j++)
    {
      if(map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'N')
        count_p++;
      if(count_p > 1)
      {
        printf("ERROR:multiple players\n");
        exit(1);
      }
      if(map[i][j] != '\n' && map[i][j] != '\t' && map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'W' && map[i][j] != 'N'&& map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != ' ')
      {
        printf("ERROR:invalid char\n");
        exit(1);
      }
    }
  }
  // check if the map if closed or not 

  return map;
}
t_cub3d *get_file_as_struct(char *path)
{
  t_list *lst = read_file(path);
  t_cub3d *cub3d = malloc(sizeof(t_cub3d));
  cub3d->textures  = get_textures(lst);
  if(cub3d->textures == NULL)
    return NULL ;
  colors_(lst , cub3d);
  cub3d->map = map_(lst);
  if(cub3d->map == NULL)
    return NULL;
  print_cub3d(cub3d);
  return cub3d;
}
