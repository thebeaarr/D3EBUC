/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madhat <madhat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:19:31 by sel-jari          #+#    #+#             */
/*   Updated: 2025/10/31 14:59:27 by madhat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void    floor_and_ceiling(t_data *data, t_ray *ray, int x)
{
    int y;

    y = 0;
    while (y < ray->draw_start)
    {
        my_mlx_pixel_put(data->img, x, y, data->cub3d->ceiling);
        y++;
    }
    
    y = ray->draw_end;
    while (y < data->win_height)
    {
        my_mlx_pixel_put(data->img, x, y , data->cub3d->floor);
        y++;
    }
}

unsigned int get_pixel_color(t_texture *tex, int x, int y)
{
    char            *pixel;
    unsigned int    color;

    pixel = tex->data.adr + (y * tex->data.line_length + x * (tex->data.bits_per_pixel / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

void draw_textured_wall(t_data *data, t_ray *ray, int x, int side)
{
    int             y;
    int             tex_y;
    int             tex_x;
    double          step;
    double          tex_pos;
    double          wall_x;
    unsigned int    color;
    t_texture       *tex;

    if (side == 0)
        tex = (ray->dir.x > 0) ? &data->texture[3] : &data->texture[2];
    else
        tex = (ray->dir.y > 0) ? &data->texture[1] : &data->texture[0];
    
    if (side == 0)
        wall_x = data->player.pos.y + ray->wall_dist * ray->dir.y;
    else
        wall_x = data->player.pos.x + ray->wall_dist * ray->dir.x;
    wall_x -= floor(wall_x);
    
    tex_x = (int)(wall_x * (double)(tex->width));
    if ((side == 0 && ray->dir.x > 0) || (side == 1 && ray->dir.y < 0))
        tex_x = tex->width - tex_x - 1;

    step = 1.0 * tex->height / ray->line_height;
    tex_pos = (ray->draw_start - data->win_height / 2 + ray->line_height / 2) * step;
    
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = get_pixel_color(tex, tex_x, tex_y);
        my_mlx_pixel_put(data->img, x, y, color);
        y++;
    }
    
    floor_and_ceiling(data, ray, x);
}