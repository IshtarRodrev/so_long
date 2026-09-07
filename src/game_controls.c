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

static void update_player_dir(int dx, int dy)
{
    if (dy < 0)
        g_game.player_dir = DIR_BACK;
    else if (dy > 0)
        g_game.player_dir = DIR_FRONT;
    else if (dx < 0)
        g_game.player_dir = DIR_LEFT;
    else if (dx > 0)
        g_game.player_dir = DIR_RIGHT;
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
    update_player_dir(dx, dy);
    if (ny < 0 || ny >= g_game.rows || nx < 0 || nx >= g_game.cols
        || g_game.map[ny][nx] == '1')
    {
        render_map();
        return (0);
    }
    g_game.map[y][x] = '0';
    g_game.map[ny][nx] = 'P';
    g_game.player_frame++;
    render_map();
    return (0);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    (void)param;
    if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
        return ;
    if (keydata.key == MLX_KEY_ESCAPE)
        exit(0);
    if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
        move_player(0, -1);
    if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
        move_player(0, 1);
    if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
        move_player(-1, 0);
    if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
        move_player(1, 0);
}
