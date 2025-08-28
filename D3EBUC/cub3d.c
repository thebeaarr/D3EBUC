/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:31:45 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/08/12 21:02:11 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_file *get_head_map(t_file *map) {
    t_file *head_map = map;
    // we have to skip the lines that only has new line char ( '\n')
    // skip lines that has the textures and has floor and ceiling .
    // and return address of the node that is the head of the map.
    // while (m) {
    //     printf("%s", m->line);
    //     m = m->next;
    // }
    while (head_map)
    {
        if(strncmp("NO" , head_map->line , 2)  &&  strncmp("EA" , head_map->line , 2)  && strncmp("WE" , head_map->line , 2)  && strncmp("SO" , head_map->line , 2)  && strncmp("F" , head_map->line , 1 )&&strncmp("C" , head_map->line, 1)  &&  strncmp("\n" , head_map->line , ft_strlen(head_map->line)))
            break;
        head_map = head_map->next;
    }
    return head_map;
}

char **get_map(t_file *file) {
    char **map;
    t_file *tmp;

    tmp = get_head_map(file);
    t_file *cm;  // counting only the map;
    cm = tmp;
    int count_map = 0;
    while (cm) {
        count_map++;
        cm = cm->next;
    }
    map = malloc(sizeof(char *) * (count_map + 1));
    map[count_map] = NULL;
    count_map = 0;
    while (tmp) {
        map[count_map] = ft_strdup(tmp->line);
        tmp = tmp->next;
        count_map++;
    }
    return map;
}

t_textures *dup_textures(t_textures *txt)
{
    t_textures *dup ;
    dup = malloc(sizeof(t_textures));
    dup->ea  = ft_strdup(txt->ea);
    dup->we  = ft_strdup(txt->we);
    dup->so  = ft_strdup(txt->so);
    dup->no  = ft_strdup(txt->no);
    return dup ;
}
t_map *parse_cub_file(char *input) {
    if (!valid_path_input(input)) return NULL;
    int fd = open(input, O_RDONLY);
    if (fd < 0) {
        printf("file not exist.\n");
        return NULL;
    }
    t_lstfile *lst = r_file(fd);
    close(fd);
    if (valid_file(lst) == false) {
        printf("ERROR:\n");
        free_lstfile(lst);
        return NULL;
    }
    t_map *map;
    map = malloc(sizeof(t_map));
    map->ceiling = lst->ceiling;
    map->floor = lst->floor;
    map->map = get_map(lst->head);
    map->txt = dup_textures(lst->txts);

    free_lstfile(lst);
    return map;
}

int main(int ac, char **av)
{
    t_map *map;
    if (ac == 2) {
        if (!(map = parse_cub_file(av[1]))) return 1;
    } else {
        printf("example of input : map/smthng.cub\n");
    }
}
