#include "mlx.h"
#include "so_long.h"

#define TILE_SIZE 40

int tile_color(char tile)
{
    if (tile == '1')
        return (0x3A3A3A);
    if (tile == 'C')
        return (0xFFD700);
    if (tile == 'E')
        return (0x32CD32);
    if (tile == 'P')
        return (0xFF4D4D);
    return (0x111111);
}

void draw_tile(int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mlx_pixel_put(g_game.mlx, g_game.win,
                x * TILE_SIZE + j, y * TILE_SIZE + i, color);
            j++;
        }
        i++;
    }
}

void render_map(void)
{
    int y;
    int x;

    mlx_clear_window(g_game.mlx, g_game.win);
    y = 0;
    while (y < g_game.rows)
    {
        x = 0;
        while (x < g_game.cols)
        {
            draw_tile(x, y, tile_color(g_game.map[y][x]));
            x++;
        }
        y++;
    }
}
