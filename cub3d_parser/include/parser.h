#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "../../libft/libft.h"
#include "../../libft/get_next_line/get_next_line.h"
#include "../../minilibx-linux/mlx.h"

// linked list for file reader
typedef struct s_file 
{
  char *line;
  struct s_file *next;

} t_file;

typedef struct  s_list
{
  t_file *head;
  t_file *ptr_hold;
} t_list;


// the map 
typedef struct s_cub3d
{
  char **map;       // the map ;
  int *colors;      // floor 1 , ceiling 2
  char ***textures; // textures
} t_cub3d;
t_file *anode(char *line);
void add_back(t_list *head, t_file *current);
char ***get_textures(t_list *lst);
int get_color(char *file);
int *get_fc(t_list *lst);
char **get_map(t_list *lst);
t_cub3d *main_parser(char *file);
void print_cub3d(t_cub3d *cub3d);
#endif
