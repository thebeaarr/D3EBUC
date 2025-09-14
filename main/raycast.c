#include "../mlx_init/include/cub3d_mlx.h"


void cast_single_ray(t_data *data, float ray_angle, int column)
{
    float ray_x;
    float ray_y;
    float ray_dir_x;
    float ray_dir_y;
    float distance;
    int hit;
    int side;
    int map_x;
    int map_y;
    float delta_dist_x;
    float delta_dist_y;
    float side_dist_x;
    float side_dist_y;
    int step_x;
    int step_y;

    ray_x = data->position.x + 20;
    ray_y = data->position.y + 20;
    ray_dir_x = cosf(ray_angle);
    ray_dir_y = sinf(ray_angle);
    distance = 0;
    hit = 0;
    map_x = (int)(ray_x / 40);
    map_y = (int)(ray_y / 40);
    delta_dist_x = fabsf(1 / ray_dir_x);
    delta_dist_y = fabsf(1 / ray_dir_y);
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x =(ray_x - map_x * 40) * delta_dist_x /40;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((map_x+ 1) *40 - ray_x) * delta_dist_x /40;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (ray_y - map_y *40) * delta_dist_y / 40;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((map_y + 1)*40 -ray_y) *delta_dist_y / 40;
    }
    // for (int y = 0; y < 800; y++)
	// {
	// 	for (int x = 0; x < 800; x++)
	// 	{
	// 		my_mlx_pixel_put(data->img, x, y, BLACK);
	// 	}
	// }
    while (!hit && distance < 800)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        distance = side == 0 ? side_dist_x : side_dist_y;
        
        if (map_x >= 0 && map_y >= 0 && data->cub3d->map[map_y] && 
            data->cub3d->map[map_y][map_x] == '1')
            hit = 1;
        // side_dist_y = ((map_y + 1)*40 -ray_y) *delta_dist_y / 40;
    }

    if (hit)
    {
        float perp_dist;
        int line_height;
        int draw_start;
        int draw_end;
        int color;
        // screen_x = j * tile + x + (int)data->position.x;
        // screen_y = i * tile + y + (int)data->position.y;

        perp_dist = distance * cosf(ray_angle - data->angle);
        line_height = (int)(800 / perp_dist);
        draw_start = -line_height / 2 + 400;
        draw_end = line_height / 2 + 400;
        
        if (draw_start < 0)
            draw_start = 0;
        if (draw_end >= 800)
            draw_end = 799;

            // my_mlx_pixel_put(data->img, column, y, color);
				// y += x / 2
        for (int y = draw_start; y < draw_end; y++)
        {
            my_mlx_pixel_put(data->img, column, y, color);
        }
    }
}

void raycast_loop(t_data *data)
{
    float fov;
    float ray_angle_increment;
    
    for (int y = 0; y < 800; y++)
    {
        for (int x = 0; x < 800; x++)
            my_mlx_pixel_put(data->img, x, y, 0);

    }
    // fov = M_PI / 3;
    ray_angle_increment = fov / 800;
    for (int x = 0; x < 800; x++)
    {
        float ray_angle;

        ray_angle = data->angle - fov / 2 + x * ray_angle_increment;
        cast_single_ray(data, ray_angle, x);
    }
    // screen_x = j * tile + x + (int)data->position.x;
    // screen_y = i * tile + y + (int)data->position.y;

}

int main(void)
{
        t_data data;
        t_cub3d cub3d;
        t_img img;
        char *map[] = {
            "11111",
            "10001",
            "10N01",
            "10001",
            "11111",
            NULL
        };
        int test_passed = 1;
    
        data.cub3d = &cub3d;
        data.img = &img;
        data.mlx = NULL;
        data.win = NULL;
        data.position.x = 80;
        data.position.y = 80;
        data.angle = 0;
        cub3d.map = map;
        img.img = NULL;
    
        printf("Starting raycasting test...\n");
    
        raycast_loop(&data);
        printf("Test 1: raycast_loop executed without crashing\n");
    
        float test_angle = data.angle;
        int hit_detected = 0;
    
        float ray_x = data.position.x + 20;
        float ray_y = data.position.y + 20;
        float ray_dir_x = cosf(test_angle);
        float ray_dir_y = sinf(test_angle);
        float distance = 0;
        int map_x = (int)(ray_x / 40);
        int map_y = (int)(ray_y / 40);
        float delta_dist_x = fabsf(1 / ray_dir_x);
        float delta_dist_y = fabsf(1 / ray_dir_y);
        float side_dist_x;
        float side_dist_y;
        int step_x;
        int step_y;
    
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (ray_x - map_x * 40) * delta_dist_x / 40;
        }
        else
        {
            step_x = 1;
            side_dist_x = ((map_x + 1) * 40 - ray_x) * delta_dist_x / 40;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (ray_y - map_y * 40) * delta_dist_y / 40;
        }
        else
        {
            step_y = 1;
            side_dist_y = ((map_y + 1) * 40 - ray_y) * delta_dist_y / 40;
        }
    
        while (distance < 1000)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
            }
            distance = side_dist_x < side_dist_y ? side_dist_x : side_dist_y;
            
            if (map_x >= 0 && map_y >= 0 && map[map_y] && map[map_y][map_x] == '1')
            {
                hit_detected = 1;
                break;
            }
        }
    
  
    
        // Test 3: Check if pixels are drawn within bounds
        int out_of_bounds = 0;
        // for (int y = 0; y < 800; y++)
        // {
        //     for (int x = 0; x < 800; x++)
        //     {
        //         if (x < 0 || x >= 800 || y < 0 || y >= 800)
        //         {
        //             out_of_bounds = 1;
        //             break;
        //         }
        //     }
        // }
  
    // }
}