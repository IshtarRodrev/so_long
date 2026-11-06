#include "libft.h"
#include "so_long.h"

#include <stdlib.h>

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
    int nx;
    int ny;

    nx = g_game.progress.player.x + dx;
    ny = g_game.progress.player.y + dy;
    update_player_dir(dx, dy);
    if (ny < 0 || ny >= g_game.rows || nx < 0 || nx >= g_game.cols
        || g_game.map[ny][nx] == '1' || is_collected(nx, ny)
        || (g_game.map[ny][nx] == 'E'
            && g_game.progress.collectibles_left > 0))
    {
        render_map();
        return (0);
    }
    g_game.move_count++;
    ft_printf("Moves: %d\n", g_game.move_count);
    if (g_game.map[ny][nx] == 'E')
    {
        ft_printf("You won!\n");
        exit(0);
    }
    g_game.progress.player = (t_point){nx, ny};
    if (g_game.map[ny][nx] == 'C')
        collect_tile(nx, ny);
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
