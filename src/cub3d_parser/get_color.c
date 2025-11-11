/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:01 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/11 20:55:58 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h" 

bool dup_c(t_file *head)
{
  t_file *current ;
  int count_f;
  int count_c;
  
  current= head;
  count_c = 0;
  count_f = 0;
  while(current)
  {
    char *tmp  = current->line;
    int index = 0;
    while(isspace(tmp[index]))
      index++;
    if(!strncmp("F" , tmp + index , 1) && isspace(tmp[index + 1]))
      count_f++;
    else if(!strncmp("C" , tmp + index , 1) && isspace(tmp[index + 1]))
      count_c++;
    if(count_f > 1 || count_c > 1)
      return true;
    current = current->next;
  }
  return (count_f != 1 || count_c != 1);
}

char *rm_spaces_check(char *s)
{
  char *new;
  int t ; 
  int index ;
  
  t = 0;
  index = 0;
  new  = malloc(sizeof(char) * ft_strlen(s) + 1);
  if(s[0] == 'C' || s[0] == 'F')
    index = 1;
  
  while(s[index] && isspace(s[index]))
    index++;
  
  while(s[index])
  {
      new[t] = s[index];
      	t++;
    index++;
  }
  new[t] = '\0';
  return new;
}
static int	count_colors(char **color)
{
	int	count;

	count = 0;
	while (color[count])
		count++;
	return (count);
}

static void	free_colors(char **color, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(color[i]);
		i++;
	}
	free(color);
}

static bool	validate_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (false);
	if (g < 0 || g > 255)
		return (false);
	if (b < 0 || b > 255)
		return (false);
	return (true);
}

static int	parse_rgb(char **color)
{
	int	r;
	int	g;
	int	b;
	int	rgb;

	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (!validate_rgb(r, g, b))
		return (-1);
	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}

int	get_color(char *s)
{
	char	*str;
	char	**color;
	int		count;
	int		rgb;

	if (!s)
		return (-1);
	str = rm_spaces_check(s);
	if (!str)
		return (-1);
	color = ft_split(str, ',');
	free(str);
	if (!color)
		return (-1);
	count = count_colors(color);
	if (count != 3)
		return (free_colors(color, count), -1);
	rgb = parse_rgb(color);
	free_colors(color, count);
	return (rgb);
}

static int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (isspace(str[i]))
		i++;
	return (i);
}

static bool	is_color_line(char *line, char type)
{
	int	index;

	index = skip_spaces(line);
	if (!strncmp(&type, line + index, 1) && isspace(line[index + 1]))
		return (true);
	return (false);
}

static void	parse_colors(t_cub3d *store, t_file *head)
{
	t_file	*current;
	char	*tmp;
	int		index;

	current = head;
	while (current)
	{
		tmp = current->line;
		index = skip_spaces(tmp);
		if (is_color_line(tmp, 'F'))
			store->floor = get_color(tmp + index);
		else if (is_color_line(tmp, 'C'))
			store->ceiling = get_color(tmp + index);
		current = current->next;
	}
}

bool	get_colors_(t_cub3d *store, t_file *head)
{
	if (dup_c(head))
	{
		printf("ERROR:duplicated colors\n");
		return (false);
	}
	store->ceiling = -1;
	store->floor = -1;
	parse_colors(store, head);
	if (store->ceiling == -1 || store->floor == -1)
	{
		printf("ERROR: Invalid color values\n");
		return (false);
	}
	return (true);
}
