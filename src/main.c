/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:35:17 by sel-jari          #+#    #+#             */
/*   Updated: 2025/11/17 16:39:08 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static bool	validate_args(int ac)
{
	if (ac != 2)
	{
		printf("ERROR: arguments\n");
		return (false);
	}
	return (true);
}

static bool	init_data(t_data *data, char *path)
{
	t_cub3d	*cub3d;

	cub3d = get_file_as_struct(path);
	printf("DEBUG: after get_file_as_struct\n");
	if (!cub3d)
	{
		free(data);
		return (false);
	}
	data->cub3d = cub3d;
	if (!init_mlx(data))
	{
		printf("ERROR: mlx init\n");
		free(data->cub3d);
		free(data);
		return (false);
	}
	return (true);
}

static void	setup_player(t_data *data)
{
	t_player	*player;

	player = &data->player;
	player->data = data;
	player_init(&data->player);
}

static void	setup_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, game, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_hook(data->win, 2, KeyPressMask, key_press, &data->player);
	mlx_hook(data->win, 3, KeyReleaseMask, key_release, &data->player);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!validate_args(ac))
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	if (!init_data(data, av[1]))
		return (1);
	setup_player(data);
	setup_hooks(data);
	mlx_loop(data->mlx);
	return (0);
}
