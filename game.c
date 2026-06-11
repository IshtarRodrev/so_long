#include "mlx.h"

#include <stdlib.h>

static int close_hook(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307)
        exit(0);
    return (0);
}

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, 640, 480, "so_long game");
    if (!win)
        return (1);
    mlx_string_put(mlx, win, 220, 230, 0xFFFFFF, "so_long ready");
    mlx_key_hook(win, close_hook, NULL);
    mlx_loop(mlx);
    return (0);
}
