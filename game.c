#include "mlx.h"
#include "so_long.h"

#include <stdlib.h>

#define TILE_SIZE 40

t_game g_game;

int main(void)
{
    g_game.mlx = mlx_init();
    if (!g_game.mlx)
        return (1);
    g_game.map = read_map_file("maps/floor1.ber");
    if (!g_game.map)
        return (1);
    g_game.win = mlx_new_window(g_game.mlx,
        g_game.cols * TILE_SIZE, g_game.rows * TILE_SIZE, "so_long demo");
    if (!g_game.win)
        return (1);
    render_map();
    mlx_key_hook(g_game.win, key_hook, NULL);
    mlx_loop(g_game.mlx);
    return (0);
}
