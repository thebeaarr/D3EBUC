#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../../libft/libft.h"
#include "../../libft/get_next_line/get_next_line.h"
#include "../../minilibx-linux/mlx.h"

typedef struct s_file 
{
  char *line;
  struct s_file *next;

} t_file;

typedef struct  s_list
{
  t_file *head_f;
  t_file *head_s;
} t_list;

typedef struct s_cub3d
{
  char **map;       // the map ;
  int floor ;
  int ceiling ;
  char ***textures; // textures
} t_cub3d;
t_cub3d *get_file_as_struct(char *path);
#endif
