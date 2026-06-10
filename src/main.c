#include <stdlib.h>
#include "so_long.h"

int main(int argc, char **argv)
{
    char **map;
    t_lay lay;

    map = check_params(argc, argv, &lay);
    if (!map)
        return (1);
    init_game(map, lay);
    return (0);
}
