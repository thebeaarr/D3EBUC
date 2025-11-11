/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:08 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/11 21:06:34 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

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
  t_file * c; 
  c = ca;
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

static bool	validate_texture(char **texture)
{
	if (!check_ntxt(texture))
		return (false);
	if (!path_valid(texture[1]))
		return (false);
	return (true);
}

static bool	process_texture_line(char ***textures, char *line, int *count)
{
	if (!is_txt(line))
		return (true);
	textures[*count] = ft_split_space(line);
	if (!validate_texture(textures[*count]))
	{
		printf("invalid textures\n");
		free_tptr(textures, *count);
		return (false);
	}
	(*count)++;
	return (true);
}

static char	***allocate_textures(void)
{
	char	***textures;

	textures = malloc(sizeof(char **) * 5);
	if (!textures)
		return (NULL);
	textures[4] = NULL;
	return (textures);
}

char	***get_textures(t_file *head)
{
	t_file	*current;
	char	***textures;
	int		count;

	if (dup_(head))
	{
		printf("duplicated textures/not enough texture!\n");
		return (NULL);
	}
	textures = allocate_textures();
	if (!textures)
		return (NULL);
	current = head;
	count = 0;
	while (current && count < 4)
	{
		if (!process_texture_line(textures, current->line, &count))
			return (NULL);
		current = current->next;
	}
	return (textures);
}

