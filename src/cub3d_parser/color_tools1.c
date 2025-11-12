/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:06:28 by madhat            #+#    #+#             */
/*   Updated: 2025/11/12 09:06:29 by madhat           ###   ########.fr       */
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
