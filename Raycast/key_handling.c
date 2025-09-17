#include "cub3d.h"

int handle_close()
{
  printf("cub3D closed\n");
  exit(1);
}

int key_press(t_keys key , t_data *data)
{
    if(key == XK_escape)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
		data->position.y += 1;
	else if (key == XK_w)
		data->position.y -= 1;
    else if (key == XK_a)
		data->position.x -= 1;
    else if (key == XK_d)
		data->position.x += 1;
    else if (key == XK_Left)
      printf("<-\n");
    else if (key == XK_Right)
      printf("->\n");
    return 0;
}

int key_release(t_keys key , t_data *data)
{
    if (key == XK_s)
		data->position.y = 0;
	else if (key == XK_w)
		data->position.y = 0;
    else if (key == XK_a)
		data->position.x = 0;
    else if (key == XK_d)
		data->position.x = 0;
    // else if (key == XK_Left)
    //   printf("<-\n");
    // else if (key == XK_Right)
    //   printf("->\n");
     return 0;
}

void	update_movement(t_data *data)
{

	if (data->position.x)
		data->position.screen_x += data->position.x * MV_SPEED;
	if (data->position.y)
		data->position.screen_y += data->position.y * MV_SPEED;
	// if (data->position.y == -1)
	// 	data->position.screen_y -= 2;
	// if (data->position.y == -1)
	// 	data->position.screen_y -= 2;
}

