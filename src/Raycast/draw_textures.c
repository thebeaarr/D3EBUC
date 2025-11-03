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

void	floor_and_scealing(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(data->img, x, y, GRAY);
		y++;
	}
	y = ray->draw_end;
	while (y < data->win_height)
	{
		my_mlx_pixel_put(data->img, x, y, 0x00404040);
		y++;
	}
}


// t_colors pick_color(t_data *data , int temp ,int x , int y  , t_ray *ray  )
// {
// 	t_colors color ;
	
// 		// if (temp == 0)
// 		// {
// 		// 	if (ray->dir.x > 0)
// 		// 		color = RED;
// 		// 	else
// 		// 		color = GREEN;
// 		// }
// 		// else
// 		// {
// 		// 	if (ray->dir.y > 0)
// 		// 		color = BLUE;
// 		// 	else
// 		// 		color = ORANGE;
// 		// }
// 		// if(x > 0 &&  x < 64 && 0)
	
// }
unsigned int get_pixel_color(t_texture *tex, int x, int y)
{
    char    *pixel;
    unsigned int color;

    if (!tex || !tex->data.adr)
        return (0xFF00FF); // debug magenta

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0x000000); // black

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
    unsigned int    color;
    t_texture       *tex;

    // Select which texture to use based on wall side and direction
    if (side == 0) // x side
        tex = (ray->dir.x > 0) ? &data->texture[3] : &data->texture[4];
    else // y side
        tex = (ray->dir.y > 0) ? &data->texture[2] : &data->texture[1];

    // Calculate X coordinate on texture
    double wall_x;
    if (side == 0)
        wall_x = data->player.pos.y + 4.5f * ray->dir.y;
    else
        wall_x = data->player.pos.x + 4.5f * ray->dir.x;
    wall_x -= floor(wall_x); // get fractional part

    tex_x = (int)(wall_x * (double)(tex->width));
    if ((side == 0 && ray->dir.x > 0) || (side == 1 && ray->dir.y < 0))
        tex_x = tex->width - tex_x - 1;

    // How much to increase texture coordinate per screen pixel
    step = 1.0 * tex->height / ray->line_height;
    tex_pos = (ray->draw_start - data->win_height / 2 + ray->line_height / 2) * step;

    // Draw the wall slice
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = get_pixel_color(tex, tex_x, tex_y);
        my_mlx_pixel_put(data->img, x, y, color);
        y++;
    }

    // Optional: draw ceiling and floor
    floor_and_scealing(data, ray, x);
}
