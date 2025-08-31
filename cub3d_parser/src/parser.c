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
  }
  printf("floor = %d\nceiling = %d\n", cub3d->ceiling , cub3d->floor); // already the map is just checked incease of the overflow
  char **map ;
  map = cub3d->map;
  for(int i = 0 ; map[i] ; i++)
    printf("map[%d] = %s" , i + 1, map[i]);// call a function that check if we have one
    // player ( just one with the sings ( E , W , S , N ))
    // the map is closed ( 1 ),
    // the map contains just 1 , 0 , or spaces , or just
}
// bool textures_valid(char ***textures_v)
// {
//   char ***textures = textures_v;
//   for(int i = 0 ; textures[i] ; i++)
//   {
//     char*clean_path = ft_substr(textures[i][1] , 0 , ft_strlen(textures[i][1]) -1 );
//     free(textures[i][1]);
//     textures[i][1] = clean_path ;
//     char *extension = ft_strrchr(textures[i][1] , '.');
//     if(strcmp(extension, ".xpm"))
//     {
//       printf("ERROR:no extension xpm in the textures\n");
//       return false;
//     }
//     int fd = open(textures[i][1] , O_RDONLY);
//     if(fd < 0)
//     {
//       printf("ERROR:textures file of %s not existed\n", textures[i][0]) ;
//       close(fd);
//       return false;
//     }
//     close(fd);
//   }
//   return true;
// }
// bool map_valid(char **map_v)
// {
//   char **map = map_v;
//   (void)map;
//   return true;
// } 


// t_cub3d *main_parser(char *file)
// {
  //   char ***txt;
  //   txt = get_textures(lst);
  //   if(!txt)
  //   {
    //     printf("ERROR:textures!");
    //     exit(1);
    //   }
    //   int *tab = get_fc(lst);
    //   if(!tab)
    //   {
      //     printf("ERROR:ceiling floor!");
      //     exit(1);
      //   }
      //   char **map = get_map(lst);
      //   if(!map)
      //   {
        //     printf("ERROR:map!");
        //     exit(1);
        //   }
        //   t_cub3d *cub3d;
        //   cub3d = malloc(sizeof(t_cub3d));
        //   cub3d->textures = txt;
        //   cub3d->colors = tab;
        //   cub3d->map = map;
        //   // print_cub3d(cub3d);
        //   // map_valid()
        //   // textures opened and closed ?
        
        //   if(!textures_valid(cub3d->textures))
        //   {
          //     printf("ERROR:map not valid\n");
          //     return NULL;
          //   }
          
          //   return cub3d;
          // }
          
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
  char *clean ;
  int index = 0;
  while(isspace(line[index]))
    index++;
  if(is_part_map(line[index]) == 0)
    return line;
  else if(is_part_map(line[index]) == -1)
    return line;
  int size = strlen(line);
  while(!isspace(line[size]))
    size--;
  clean = ft_substr(line , index , size - index);
  free(line);
  return clean ; 
}

t_list *read_file(char *file )
{
  int fd = open(file, O_RDONLY);
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
      return NULL;
    current = anode(tmp);
    if(!lst)
    {
      lst = malloc(sizeof(t_list));
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
  return  !ft_strncmp(line , "NO " , 3) || !ft_strncmp(line , "SO " , 3) || !ft_strncmp(line , "WE " , 3)|| !ft_strncmp(line , "EA " , 3);
}

char ***get_textures(t_list *lst)
{
  t_file *tmp ; 
  tmp = lst->head;
  char ***ret = malloc(sizeof(char **) * 5);
  ret[4] = NULL;
  int ind = 0;
  int count = 6;
  while(tmp && count)
  {
    if(is_txt(tmp->line))
    {
      ret[ind]  = ft_split_space(tmp->line);// normalment espace ? and how many string if more than 2 u suck return NULL 
      ind++;
    }
    count--;
    tmp = tmp->next;
  }

  if(ind != 4)
    return NULL;
  // existence 
  for(int i = 0 ; ret[i] ; i++)
  {
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
  int count = 6;
  t_file *tmp ;
  int ind = 0;
  tmp = lst->head;
  while(tmp && ind != 2 && count )
  {
    if(strncmp(tmp->line , "F " , 2) == 0)
    {
      cub3d->floor = get_color(tmp->line);
      if(cub3d->floor == -1)
      {
        printf("ERROR:problem\n");
        exit(1);  
      }
      ind++;
    }
    else if(strncmp(tmp->line , "C " , 2) == 0)
    {
      cub3d->ceiling = get_color(tmp->line);
      if(cub3d->ceiling == -1)
      {
        printf("ERROR:problem\n");
        exit(1);
      }
      ind++;
    }
    count--;
    tmp = tmp->next;
  }
  if(ind != 2)
  {
    printf("floor or ceiling are not exist !");
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
  return map;
}
t_cub3d *get_file_as_struct(char *path)
{
  t_list *lst = read_file(path);
  // t_file *tmp = lst->head;
  // while(tmp)
  // {
  //   printf("%s\n", tmp->line);
  //   tmp = tmp->next;
  // }
  // get the textures ? 
  // get the colors ? 
  // get the maps ? 
  t_cub3d *cub3d = malloc(sizeof(t_cub3d));
  cub3d->textures  = get_textures(lst);
  colors_(lst , cub3d);
  cub3d->map = map_(lst);
  print_cub3d(cub3d);
  return cub3d;
}
