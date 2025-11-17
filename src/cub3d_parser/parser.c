/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:56:13 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/11/17 16:35:10 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	free_store_partial(t_cub3d *store, t_list *list, int stage)
{
	if (stage >= 1)
		free_tptr(store->textures, 4);
	if (stage >= 2)
		free_dptr(store->map);
	free_list(list);
	free(store);
}

static bool	init_textures(t_cub3d *store, t_list *list)
{
	store->textures = get_textures(list->head_f);
	if (store->textures == NULL)
	{
		free_list(list);
		free(store);
		return (false);
	}
	return (true);
}

static bool	init_colors(t_cub3d *store, t_list *list)
{
	if (!get_colors_(store, list->head_f))
	{
		free_store_partial(store, list, 1);
		return (false);
	}
	return (true);
}

static bool	init_map(t_cub3d *store, t_list *list)
{
	store->map = get_map(list->head_s);
	if (store->map == NULL)
	{
		free_store_partial(store, list, 1);
		return (false);
	}
	free_list(list);
	if (!parse_map(store->map))
	{
		free_store_partial(store, NULL, 2);
		return (false);
	}
	return (true);
}

t_cub3d	*get_file_as_struct(char *path)
{
	t_cub3d	*store;
	t_list	*list;

	if (!path_cub(path))
		return (NULL);
	list = read_file(path);
	if (list == NULL || list->head_f == NULL || list->head_s == NULL)
	{
		printf("ERROR: Invalid file structure\n");
		exit(1);
	}
	store = malloc(sizeof(t_cub3d));
	if (!store)
		return (free_list(list), NULL);
	if (!init_textures(store, list))
		return (NULL);
	if (!init_colors(store, list))
			return (NULL);
	if (!init_map(store, list))
		return (NULL);
	return (store);
}
