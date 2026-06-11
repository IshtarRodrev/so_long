#include "so_long.h"

#include <stdlib.h>

static int find_player_local(int *x, int *y)
{
    int row;
    int col;

    row = 0;
    while (row < g_game.rows)
    {
        col = 0;
        while (col < g_game.cols)
        {
            if (g_game.map[row][col] == 'P')
            {
                *x = col;
                *y = row;
                return (1);
            }
            col++;
        }
        row++;
    }
    return (0);
}

int find_player(int *x, int *y)
{
    return (find_player_local(x, y));
}

int move_player(int dx, int dy)
{
    int x;
    int y;
    int nx;
    int ny;

    if (!find_player(&x, &y))
        return (0);
    nx = x + dx;
    ny = y + dy;
    if (ny < 0 || ny >= g_game.rows || nx < 0 || nx >= g_game.cols)
        return (0);
    if (g_game.map[ny][nx] == '1')
        return (0);
    g_game.map[y][x] = '0';
    g_game.map[ny][nx] = 'P';
    render_map();
    return (0);
}

int key_hook(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307)
        exit(0);
    if (keycode == 65362 || keycode == 119 || keycode == 87)
        return (move_player(0, -1));
    if (keycode == 65364 || keycode == 115 || keycode == 83)
        return (move_player(0, 1));
    if (keycode == 65361 || keycode == 97 || keycode == 65)
        return (move_player(-1, 0));
    if (keycode == 65363 || keycode == 100 || keycode == 68)
        return (move_player(1, 0));
    return (0);
}
