#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/*
** The map stays exactly as it was loaded. Everything that changes during play
** is kept here: the player's position and which tiles have been collected.
*/
void progress_init(const t_lay *lay)
{
    g_game.progress.collected = ft_calloc(lay->rows * lay->cols, sizeof(bool));
    if (!g_game.progress.collected)
    {
        ft_printf("Error: memory allocation failed\n");
        exit(1);
    }
    g_game.progress.player = lay->player;
    g_game.progress.collectibles_left = lay->collectibles;
    g_game.progress.collectibles_total = lay->collectibles;
}

bool is_collected(int mx, int my)
{
    return (g_game.progress.collected[(size_t)my * g_game.cols + mx]);
}

void collect_tile(int mx, int my)
{
    g_game.progress.collected[(size_t)my * g_game.cols + mx] = true;
    g_game.progress.collectibles_left--;
}
