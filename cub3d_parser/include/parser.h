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
  t_file *head_f; // first -> texutres c f .
  t_file *head_s;// map_s ;
} t_list;

typedef struct s_cub3d
{
  char **map;       // the map ;
  int floor ;
  int ceiling ;
  char ***textures; // textures
} t_cub3d;
bool parse_map(char **map);
char **get_map(t_file *head);
char	**ft_split_space(const char *s);
t_cub3d *get_file_as_struct(char *path);
bool isspaces(char *line);
void add_back(t_file **head, t_file *current);
t_file *anode(char *line);
t_list *read_file(char *path);
char ***get_textures(t_file *head);
bool get_colors_(t_cub3d *store , t_file *head);
bool is_player(char c);
void print_cub3d(t_cub3d *cub3d);
int size_list(t_file *head);
#endif
