#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>
# include "MLX42.h"

# define TILE_SIZE 40
# define MENU_WIN_W 1200
# define MENU_WIN_H 800
# define VIEWPORT_COLS (MENU_WIN_W / TILE_SIZE)
# define VIEWPORT_ROWS (MENU_WIN_H / TILE_SIZE)
# define CAMERA_MARGIN 5
# define MENU_MAX_MAPS 9
# define SPRITE_DIR "assets/sprites"
# define SPRITE_FRAMES 16
# define DIR_FRONT 0
# define DIR_BACK 1
# define DIR_LEFT 2
# define DIR_RIGHT 3
# define DIR_COUNT 4

typedef struct s_game
{
    mlx_t *mlx;
    mlx_image_t *img;
    char **map;
    int rows;
    int cols;
    char *map_names[MENU_MAX_MAPS];
    int map_count;
    mlx_image_t *menu_imgs[MENU_MAX_MAPS + 1];
    int menu_img_count;
    mlx_image_t *status_img;
    int cam_x;
    int cam_y;
    int view_cols;
    int view_rows;
    mlx_texture_t *player_tex[DIR_COUNT][SPRITE_FRAMES];
    int player_frame_count[DIR_COUNT];
    int player_dir;
    int player_frame;
} t_game;

extern t_game g_game;

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
char **read_map_file(const char *path);
int parse_map_file(const char *path, t_map *map);
int validate_map(const t_map *map);
int path_is_valid(const t_map *map);
void free_map(t_map *map);
int has_valid_extension(const char *path);
char **load_and_validate(const char *path, t_lay *lay);
void init_game(void);
void start_map_menu(void);
int tile_color(char tile);
void draw_tile(int x, int y, int color);
void load_player_sprites(void);
void draw_player_tile(int x, int y);
void init_camera(void);
void update_camera(void);
void render_map(void);
int find_player(int *x, int *y);
int move_player(int dx, int dy);
void key_hook(mlx_key_data_t keydata, void *param);

#endif
