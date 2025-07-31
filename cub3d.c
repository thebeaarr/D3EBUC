/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:31:45 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/31 18:16:21 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"


t_lstfile *parse_cub_file(char *input)
{
  if(!valid_path_input(input))
    return NULL;
  int fd = open(input, O_RDONLY );
  if(fd < 0)
  {
    printf("file not exist.\n");
    return NULL;
  }
  t_lstfile *lst = r_file(fd);
  close(fd);
  if (valid_file(lst) == false)
  {
    printf("failed :(\n");
    free_lstfile(lst);
    return NULL;
  }
  return lst;
}

int main(int ac, char **av)
{
  t_lstfile *lst;
  if (ac == 2)
  {
    if(!(lst = parse_cub_file(av[1])))
      return 1;
    print_cfile(lst);
    free_lstfile(lst);
  }
  else 
  {
    printf("example of input : map/smthng.cub\n");
  }
}
