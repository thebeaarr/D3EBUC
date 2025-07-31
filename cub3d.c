/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:31:45 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/31 17:58:23 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int main(int ac, char **av)
{
  if(ac == 2)
  {
    if(!valid_path_input(av[1]))
      return 1;
    int fd = open(av[1], O_RDONLY );
    if(fd < 0)
    {
      printf("file not exist.\n");
      return 1;
    }
    t_lstfile *lst = r_file(fd);
    close(fd);
    print_cfile(lst);
    if (valid_file(lst) == false)
    {
      printf("failed :(\n");
      free_lstfile(lst);
      return 1;
    }
    printf("\nsuccessed to run the cube 3d.!!!\n");
    free_lstfile(lst);
  }
  else 
  {
    printf("example of input : map/smthng.cub\n");
  }
}
