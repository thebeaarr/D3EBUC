#include "../include/parser.h"

bool check_align(t_lst *head)
{
    t_file *_tmp = head->head;
    int _count = 0;

    while (_tmp)
    {
        char *_tmpc = _tmp->line;
        if (strncmp("EA", _tmpc, 2) == 0 ||
            strncmp("WE", _tmpc, 2) == 0 ||
            strncmp("NO", _tmpc, 2) == 0 ||
            strncmp("SO", _tmpc, 2) == 0)
        {
            _count++;
        }
        else if (_tmpc[0] == '\n' || _tmpc[0] == '\0')
        {
            _tmp = _tmp->next;
            continue;
        }
        else
            break;
        _tmp = _tmp->next;
    }
    return (_count == 4);
}

int count_strings(char **words)
{
    int i = 0;
    while (words && words[i])
        i++;
    return i;
}

bool valid_config(t_textures *head)
{
    char ***textures = head->textures;
    for (int i = 0; i < 4; i++)
    {
        int counter = count_strings(textures[i]);
        if (counter != 2)
            return false;

        char *tmp = strrchr(textures[i][1], '.');
        if (!tmp || strcmp(tmp, ".xpm") != 0)
            return false;
    }
    return true;
}

t_textures *get_textures(t_lst *head)
{
    if (!check_align(head))
    {
        printf("ERROR: textures\n");
        return NULL;
    }
    t_textures *textures = malloc(sizeof(t_textures));
    if (!textures)
        return NULL;
    textures->textures = malloc(sizeof(char **) * 4);
    if (!textures->textures)
    {
        free(textures);
        return NULL;
    }
    t_file *_tmp = head->head;
    int i = 0;
    while (_tmp && i < 4)
    {
        if (strncmp("EA", _tmp->line, 2) == 0 ||
            strncmp("WE", _tmp->line, 2) == 0 ||
            strncmp("SO", _tmp->line, 2) == 0 ||
            strncmp("NO", _tmp->line, 2) == 0)
        {
            textures->textures[i++] = ft_split(_tmp->line, 32);
        }
        else if(_tmp->line[0] != '\0' || _tmp->line[0] != '\n')
          break;
        _tmp = _tmp->next;
    }
    if (!valid_config(textures))
    {
        printf("ERROR: invalid config\n");
        return NULL;
    }
    return textures;
}

int get_color(char *color)
{
  char **clr = ft_split(color , 32);
  if(count_strings(clr) !=2 )
    return -1;
  char **types = ft_split(clr[1] , ',');
  if(count_strings(types) != 3 )
    return -1;
  int r = ft_atoi(types[0]);
  int g = ft_atoi(types[1]);
  int b = ft_atoi(types[2]);
  if(r == -1 || g == -1 || b == -1)
    return -1;
  int rgb = (r << 16) || (g << 8) || b ;
  return rgb;
}
int *get_fc(t_lst *head)
{
  t_file *_tmp;
  _tmp = head->head;
  // skiping textures and files;
  while(strncmp("EA", _tmp->line, 2) == 0 ||
            strncmp("WE", _tmp->line, 2) == 0 ||
            strncmp("SO", _tmp->line, 2) == 0 ||
            strncmp("NO", _tmp->line, 2) == 0 ||
            _tmp->line[0] == '\n')
            {
              _tmp = _tmp->next;
            }
  int *color = malloc(sizeof(int) * 2); // first is for F , and second if for C
  int i = 0 ;

  while(_tmp && i != 2)
  {
    if(strncmp("F" , _tmp->line , 1) == 0)
    {
      color[0] = get_color(_tmp->line);
      if(color[0] == -1)
      {
        return NULL;
      }
      i++;
    }
    else if(strncmp("C" , _tmp->line, 1) == 0)
    {
      color[1] = get_color(_tmp->line);
      if(color[1] == -1)
        return NULL;
      i++;
    }
    else if(_tmp->line[0] == '\n')
    {
      _tmp = _tmp->next;
      continue ;
    }
    else
      break;
    _tmp = _tmp->next;
  }
  if(i != 2)
    return NULL;
  return color;
}
