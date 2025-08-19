#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include <string.h>
int *get_fc(t_lst *head);
t_textures *get_textures(t_lst *head);
#endif
