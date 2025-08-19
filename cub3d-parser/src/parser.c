#include "parser.h"

void _aback(t_lst *_head,  t_file *current)
{
  t_file *_tmp ;
  _tmp = _head->head ;
  while(_tmp->next)
    _tmp = _tmp->next;
  _tmp->next = current ;
  current->next = NULL;
}
t_file  *_bnode(char *_line)
{
  t_file *_node ;
  _node = malloc(sizeof(t_file));
  _node->line = _line ;
  _node->next = NULL;
}

t_lst *_readf(char *_file)
{
  t_file *_current;
  char *_tmp ;
  int _fd;
  _fd=  open(_file , O_RDONLY);
  if(_fd < 0)
  {
    printf("ERROR:file not opened\n");
    exit(1);
  }
  t_lst *_lst = malloc(sizeof(t_lst));
  _lst->head = NULL;
  t_file *tmp;
  while((_tmp = get_next_line(_fd)))
  {
    if(_tmp)
      _current = _bnode(_tmp);
    if(!_lst->head)
    {
      _lst->head = _current;
      tmp = _lst->head;
    }
    else
    {
      tmp->next = _current;
      tmp = tmp->next;
    }
  }
  return _lst;
}

t_cub3d *_cub3d_paser(char *_file)
{
  t_lst *_lst ;
  t_cub3d *_cub3d ;
  // what to do righnt now is read from the
  t_lst *head = _readf(_file);
  // reading and storing textures ;
  _cub3d = malloc(sizeof(t_cub3d));
  _cub3d->textures = get_textures(head);
  _cub3d->colr = get_fc(head);
  _cub3d->map = get_map(head);
}
