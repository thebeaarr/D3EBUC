#include <stdio.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"

#define MAX_KEYS 1024
int keys[MAX_KEYS]; // array to track which keys are pressed

// KeyPress hook — only one per window
int key_press(int keycode, void *param)
{
    if (keycode >= 0 && keycode < MAX_KEYS)
        keys[keycode] = 1;
    return 0;
}

// KeyRelease hook — only one per window
int key_release(int keycode, void *param)
{
    if (keycode >= 0 && keycode < MAX_KEYS)
        keys[keycode] = 0;
    return 0;
}

// Update loop called continuously
int update(void *param)
{
    // Example Linux keycodes for W/A/S/D
    if (keys[25]) // W
        printf("Moving up\n");
    if (keys[38]) // A
        printf("Moving left\n");
    if (keys[39]) // S
        printf("Moving down\n");
    if (keys[40]) // D
        printf("Moving right\n");

    // Example combination
    if (keys[25] && keys[38])
        printf("Moving up-left!\n");
    if (keys[25] && keys[40])
        printf("Moving up-right!\n");
    if (keys[39] && keys[38])
        printf("Moving down-left!\n");
    if (keys[39] && keys[40])
        printf("Moving down-right!\n");

    return 0;
}

int main()
{
    void *mlx = mlx_init();
    if (!mlx)
    {
        fprintf(stderr, "Failed to init MLX\n");
        return 1;
    }

    void *win = mlx_new_window(mlx, 800, 600, "Multi-key test");
    if (!win)
    {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }

    // Only one hook per event type
    mlx_hook(win, 2, 1L<<0, key_press, NULL);    // KeyPress
    mlx_hook(win, 3, 1L<<1, key_release, NULL);  // KeyRelease
    mlx_loop_hook(mlx, update, NULL);            // continuous update

    mlx_loop(mlx);
    return 0;
}
