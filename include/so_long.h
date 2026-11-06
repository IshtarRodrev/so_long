#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>
# include "MLX42.h"

# define TILE_SIZE 40
# define SCORE_BAR_HEIGHT 16
# define SCORE_BAR_BORDER 2
# define MENU_WIN_W 1200
# define MENU_WIN_H 800
# define VIEWPORT_COLS (MENU_WIN_W / TILE_SIZE)
# define VIEWPORT_ROWS (MENU_WIN_H / TILE_SIZE)
# define CAMERA_MARGIN 5
# define MENU_MAX_MAPS 9
# define MAPS_DIR "maps"
# define SPRITE_DIR "assets/sprites"
# define EXIT_SPRITE_PATH "assets/sprites/exit_tile.png"
# define BROKEN_SIGN_SPRITE_PATH "assets/sprites/broken_sign_tile.png"
# define WALL_DOWN_SPRITE_PATH "assets/sprites/wall_down.png"
# define SHOWER_RIGHT_SPRITE_PATH "assets/sprites/shower_right.png"
# define SHOWER_LEFT_SPRITE_PATH "assets/sprites/shower_left.png"
# define GLASS_DOWN_RIGHT_SPRITE_PATH "assets/sprites/glass_fence_down_right.png"
# define GLASS_DOWN_LEFT_SPRITE_PATH "assets/sprites/glass_fence_down_left.png"
# define FACE_DOWN 0
# define FACE_UP 1
# define FACE_LEFT 2
# define FACE_RIGHT 3
# define FACE_COUNT 4
# define SPRITE_FRAMES 16
# define DIR_FRONT 0
# define DIR_BACK 1
# define DIR_LEFT 2
# define DIR_RIGHT 3
# define DIR_COUNT 4

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_progress
{
	t_point	player;
	bool	*collected;
	int		collectibles_left;
	int		collectibles_total;
}	t_progress;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	int				rows;
	int				cols;
	char			*map_names[MENU_MAX_MAPS];
	int				map_count;
	mlx_image_t		*menu_imgs[MENU_MAX_MAPS + 1];
	int				menu_img_count;
	mlx_image_t		*status_img;
	int				cam_x;
	int				cam_y;
	int				view_cols;
	int				view_rows;
	mlx_texture_t	*player_tex[DIR_COUNT][SPRITE_FRAMES];
	int				player_frame_count[DIR_COUNT];
	int				player_dir;
	int				player_frame;
	mlx_texture_t	*exit_tex;
	mlx_texture_t	*broken_sign_tex;
	mlx_texture_t	*facing_wall_tex;
	mlx_texture_t	*glass_down_right_tex;
	mlx_texture_t	*glass_down_left_tex;
	mlx_texture_t	*shower_tex[FACE_COUNT];
	mlx_texture_t	*desk_tex[FACE_COUNT];
	mlx_texture_t	*table_tex[FACE_COUNT];
	mlx_texture_t	*toilet_tex[FACE_COUNT];
	mlx_texture_t	*lockers_tex[FACE_COUNT];
	mlx_texture_t	*sink_tex[FACE_COUNT];
	mlx_texture_t	*kitchen_tex[FACE_COUNT];
	mlx_texture_t	*coffee_tex[FACE_COUNT];
	mlx_texture_t	*water_cooler_tex[FACE_COUNT];
	mlx_texture_t	*fridge_tex[FACE_COUNT];
	mlx_texture_t	*vending_tex[FACE_COUNT];
	int				move_count;
	t_progress		progress;
}	t_game;

typedef struct s_map
{
	char	**lines;
	size_t	rows;
	size_t	cols;
	t_point	player;
	int		collectibles;
	int		exits;
}	t_map;

typedef struct s_path_search
{
	const t_map	*map;
	bool		*visited;
	int			*queue;
	size_t		qend;
	int			found_collectibles;
	int			found_exits;
	int			leaked;
}	t_path_search;

typedef struct s_run
{
	char	first;
	char	last;
	int		index;
	int		length;
}	t_run;

typedef enum e_tile
{
	TILE_EMPTY = '0',
	TILE_WALL = '1',
	TILE_COLLECTIBLE = 'C',
	TILE_EXIT = 'E',
	TILE_PLAYER = 'P'
}	t_tile;

typedef t_map	t_lay;

/* controls.c */
void			init_game(t_game *game);

/* menu.c */
int				scan_maps_dir(t_game *game);
void			draw_map_list(t_game *game);

/* menu_transition.c */
void			show_status(t_game *game, const char *msg);
void			start_game(t_game *game, char **map);

/* menu_keys.c */
void			start_map_menu(t_game *game);

/* map/map.c */
char			*read_file_to_string(const char *path);
int				parse_map_file(const char *path, t_map *map);
int				validate_map(const t_map *map);
void			free_map(t_map *map);

/* map/map_path.c */
void			search_from_player(t_path_search *s);
int				collectible_is_trapped(t_path_search *s);

/* map/map_path_check.c */
int				map_error(const char *msg);
int				path_is_valid(const t_map *map);

/* map/map_read.c */
char			**read_map_file(t_game *game, const char *path);

/* map/params.c */
int				has_valid_extension(const char *path);
char			**load_and_validate(t_game *game, const char *path, t_lay *lay);

/* progress/progress.c */
void			progress_init(t_game *game, const t_lay *lay);
bool			is_collected(t_game *game, int mx, int my);
void			collect_tile(t_game *game, int mx, int my);

/* camera/camera.c */
void			init_camera(t_game *game);
void			update_camera(t_game *game);

/* game_controls.c */
int				move_player(t_game *game, int dx, int dy);
void			key_hook(mlx_key_data_t keydata, void *param);

/* game_render.c */
void			load_player_sprites(t_game *game);

/* game_render_texture.c */
void			draw_texture_tile(t_game *game, mlx_texture_t *layers[2],
					t_point pos, uint32_t bg);
void			draw_player_tile(t_game *game, int x, int y);
void			load_exit_sprite(t_game *game);

/* game_render_tiles.c */
int				tile_color(char tile);
void			draw_exit_tile(t_game *game, int x, int y);
void			draw_tile(t_game *game, int x, int y, int color);

/* game_render_map.c */
void			render_map(t_game *game);

/* patterns/patterns.c */
void			load_pattern_sprites(t_game *game);

/* patterns/patterns_tile.c */
char			tile_at(t_game *game, int mx, int my);
bool			is_corridor(t_game *game, int mx, int my);
mlx_texture_t	*facing_wall_texture(t_game *game, int mx, int my);

/* patterns/patterns_runs.c */
bool			is_equipment_run(char first, char last, int length);
mlx_texture_t	*run_texture(t_game *game, t_run run, int face);

/* patterns/patterns_lines.c */
bool			column_sprite(t_game *game, int mx, int my,
					mlx_texture_t **sprite);
mlx_texture_t	*row_texture(t_game *game, int mx, int my);

/* patterns/patterns_desks.c */
bool			is_sideways_desk(t_game *game, int mx, int my);
mlx_texture_t	*empty_table_texture(t_game *game, int mx, int my);

/* patterns/patterns_collectible.c */
mlx_texture_t	*collectible_tile_texture(t_game *game, int mx, int my);

#endif
