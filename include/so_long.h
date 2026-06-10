#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_point
{
    int x;
    int y;
} t_point;

typedef struct s_map
{
    char **lines;
    size_t rows;
    size_t cols;
    t_point player;
    int collectibles;
    int exits;
} t_map;

typedef enum e_tile
{
    TILE_EMPTY = '0',
    TILE_WALL = '1',
    TILE_COLLECTIBLE = 'C',
    TILE_EXIT = 'E',
    TILE_PLAYER = 'P'
} t_tile;

typedef t_map t_lay;

char *read_file_to_string(const char *path);
int parse_map_file(const char *path, t_map *map);
int validate_map(const t_map *map);
int path_is_valid(const t_map *map);
void free_map(t_map *map);
char **check_params(int argc, char **argv, t_lay *lay);
void init_game(char **map, t_lay lay);

#endif
