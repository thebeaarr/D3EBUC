#ifndef PARSING_H
#define  PARSING_H
#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
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
  int floor;
  int ceiling;
} t_lstfile;
// what excuter will see 

typedef struct s_map
{
  int floor;
  int ceiling;
  char **map;
  t_textures *txt; 
} t_map;

bool		valid_file(t_lstfile *lst);
bool		get_path_txts(t_lstfile **lst);
void		free_lstfile(t_lstfile *lst);
bool		all_txt_set(t_textures *t);
bool		texture_exist(t_textures *t);
bool		get_txt_path(t_textures **tx, char *txt);
bool		dup_dir(t_textures *t, char *dir);
bool		valid_path_xpm(char *path);
bool		is_txt(char *path);
void 		print_cfile(t_lstfile *lst);
t_lstfile	*r_file(int fd);
bool		valid_path_input(char *path);

#endif