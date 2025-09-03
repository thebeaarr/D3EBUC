#include "../include/parser.h"

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

void free_dptr(char **txt)
{
	int index;

	index = 0;
	while(txt[index])
	{
		free(txt[index]);
		index++;
	}
	free(txt);
	txt = NULL;
}

void free_tptr(char ***textures , int count )
{
	int index;

	index = 0;
	while(index < count)
	{
		free_dptr(textures[index]);
		index++;
	}
	free(textures);
	textures = NULL;
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
		free_tptr(textures , count);
		return NULL;
      }
      count++;
    }
    current = current->next;
  }
  return textures;
}
