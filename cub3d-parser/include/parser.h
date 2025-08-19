#ifndef PARSER_H
#define PARSER_H
#include "map_loader.h"
#include "config_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../libft/get_next_line/get_next_line.h"
#include "../../libft/libft.h"

typedef struct s_textues
{
  char ***textures;
} t_textures;

// the main struct to load on it the file.cub
typedef struct s_cub3d
{
  char **map ;
  t_textures *textures;
  int *colr ; // F , C
}t_cub3d;


// linked list to load on it the file.cub
typedef struct s_file
{
  char *line ;
  struct s_file *next;
} t_file ;
typedef struct s_lst
{
  t_file *head;
}t_lst;
#endif
