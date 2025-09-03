#include "../include/parser.h"

t_file *anode(char *line)
{
	t_file *node = malloc(sizeof(t_file));
	if(line[strlen(line) - 1] == '\n')
		node->line = ft_substr(line , 0 , strlen(line) - 1);
	else
		node->line = strdup(line);
	node->next = NULL;
	return node;
}

void add_back(t_file **head, t_file *current)
{
  t_file *tmp;
  tmp = *head;
  while(tmp->next)
    tmp = tmp->next;
  tmp->next = current;
}

bool isspaces(char *line)
{
  int i = 0;
  while(line[i])
  {
    if(!isspace(line[i]))
      return false;
    i++;
  }
  return line[i] == '\0';
}
