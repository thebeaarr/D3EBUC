#include "../mlx_init/include/cub3d_mlx.h"

int handle_close()
{
  printf("cub3D closed\n");
  exit(1);
}

int key_press(t_keys key , t_data *data)
{
    (void)data;
    if(key == 65307)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
	{
		data->position.y += 1;
    	printf("s\n");
	}
	else if (key == XK_w)
	{

		data->position.y -= 1;
		printf("w\n");
	}
    else if (key == XK_a)
	{

		data->position.x -= 1;
		printf("a\n");
	}
    else if (key == XK_d)
	{
		data->position.x += 1;
		printf("d\n");
	}
    else if (key == XK_Left)
	{

      printf("<-\n");
	}
    else if (key == XK_Right)
	{

      printf("->\n");
	}
    return 0;
}

int key_release(t_keys key , t_data *data)
{
    (void)data;
    if(key == 65307)
    {
      printf("cub3D closed(Esc)\n");
	//   free_all_exit()
      exit(0);
    }
    else if (key == XK_s)
      printf("relase s\n");
    else if (key == XK_a)
      printf("release a\n");
    else if (key == XK_d)
      printf("release d\n");
    else if (key == XK_w)
      printf("release w\n");
    else if (key == XK_Left)
      printf("release <-\n");
    else if (key == XK_Right)
      printf("release ->\n");
    return 0;
}