/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:31:45 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/31 06:45:42 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
// we have first to parse the input and read the file and 
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
typedef struct s_file
{
  char *line;
  struct s_file *next;
} t_file;
typedef struct s_textures
{
  char *no;
  char *so;
  char *ea;
  char *we;
} t_textures;

typedef struct s_lstfile
{
  t_file *head;
  t_textures *txts;  
} t_lstfile;

// nothing but we just making sure path is valid 
bool valid_path_input(char *path)
{
  char *dot = strrchr(path, '.');
  if(dot && strcmp("cub" , dot + 1) == 0)
    return true;
  return false;
}

// buidling list of lines to get the file and close the fd ; 
t_lstfile *r_file(int fd)
{
  t_lstfile *(lst);
  lst = malloc(sizeof(t_lstfile));
  if (!lst)
    return NULL;
  t_file *head = NULL;
  t_file *current = NULL;
  char *tmp;
  while ((tmp = get_next_line(fd)))
  {
    t_file *new_node = malloc(sizeof(t_file));
    if (!new_node)
      return NULL;
    new_node->line = tmp;
    new_node->next = NULL;
    if (!head)
    {
      head = new_node;
      current = new_node;
    }
    else
    {
      current->next = new_node;
      current = new_node;
    }
  }
  lst->head = head;
  return lst;
}

void print_cfile(t_lstfile *lst)
{
  t_file *file = lst->head;
  while (file)
  {
    printf("%s", file->line);
    file = file->next;
  }
}
bool is_txt(char *path)
{
  return (!strncmp(path, "NO", 2) || !strncmp(path, "WE", 2) || !strncmp(path, "EA", 2) || !strncmp(path, "SO", 2));
}

bool valid_path_xpm(char *path)
{
  char *xpm = strrchr(path, '.');
  if(strncmp(xpm , ".xpm" , 4 ) ==0)
    return true;
  return false;
}
bool dup_dir(t_textures *t , char *dir )
{
  if(t->ea && strncmp(dir , "EA" , 2) == 0)
    return false;
  else if(t->no && strncmp(dir , "NO" , 2) == 0)
    return false;
  else if(t->so && strncmp(dir , "SO" , 2) == 0)
    return false;
  else if(t->we && strncmp(dir , "WE" ,2) == 0)
    return false;
  return true;
}
bool get_txt_path(t_textures **tx , char *txt)
{
  t_textures *x = *tx;
  char *path = strchr(txt, '.');
  if(dup_dir(x ,path))
  {
    write(2, path, 2);
    return false;
  }
  if(!valid_path_xpm(path))
  {
    printf("not valid path xpm!\n");
    return false;
  }
  if(strncmp(txt , "NO" , 2) == 0)
    x->no = strdup(path);
  else if(strncmp(txt , "WE" , 2) == 0)
    x->we = strdup(path);
  else if(strncmp(txt, "SO" , 2) == 0)
    x->so = strdup(path);
  else if(strncmp(txt, "EA", 2) == 0)
    x->ea = strdup(path);
  else
    return false;
  return true;
}

bool all_txt_set(t_textures *t)
{
  return (t->ea && t->no && t->so && t->we);
}

bool get_path_txts(t_lstfile **lst)
{
  t_lstfile *l = *lst;
  t_textures *t;
  t = malloc(sizeof(t_textures));
  t_file *tmp;
  t->ea = NULL;
  t->no = NULL;
  t->so = NULL;
  t->we = NULL;
  tmp = l->head;
  while(tmp)
  {
    if(is_txt(tmp->line))
    { 
        if(!get_txt_path(&t, tmp->line))
          return false;
        if (all_txt_set(t))
          break;
    }
    tmp = tmp->next;
  }
  if(!all_txt_set(t))
    return false;
  l->txts = t;
  return true;
}

bool valid_file(t_lstfile *lst)
{
  t_file *(file);
  file = lst->head;
  bool r;
  r = false;
  r = get_path_txts(&lst);
  return r;
}

int main(int ac, char **av)
{
  if(ac == 2)
  {
    if(!valid_path_input(av[1]))
      return 1;
    int fd = open(av[1], O_RDONLY );
    if(fd < 0)
    {
      printf("file not exist.\n");
      return 1;
    }
    t_lstfile *lst = r_file(fd);
    close(fd);
    // print_cfile(lst);
    if (valid_file(lst) == false)
    {
      printf("failed :(\n");
      return 1;
    }
    printf("\nsuccessed to run the cube 3d.!!!\n");
  }
  else 
  {
    printf("example of input : map/smthng.cub\n");
  }
}
