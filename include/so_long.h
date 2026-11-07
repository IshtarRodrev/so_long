/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 22:25:29 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 22:25:35 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stddef.h>
# include "MLX42.h"

# define TILE_SIZE 40
# define SCORE_BAR_HEIGHT 16
# define SCORE_BAR_BORDER 2
# define WINDOW_W 1200
# define WINDOW_H 800
# define VIEWPORT_COLS 30
# define VIEWPORT_ROWS 20
# define CAMERA_MARGIN 5
# define MAX_COLLECTIBLES 10
# define ASPHALT_ROWS 3
# define TREE_SPACING 6
# define WINDOW_MIN_RUN 6
# define MENU_LINES 2
# define MAPS_DIR "maps"
# define SPRITE_DIR "assets/sprites"
# define DIR_DOWN 0
# define DIR_UP 1
# define DIR_LEFT 2
# define DIR_RIGHT 3
# define DIR_COUNT 4
# define SPRITE_FRAMES 16
# define IMG_CACHE 96
# define GLASS_DOWN_RIGHT_LEFT 0
# define GLASS_DOWN_RIGHT_RIGHT 1
# define GLASS_DOWN_LEFT_LEFT 2
# define GLASS_DOWN_LEFT_RIGHT 3
# define GLASS_SIDES 4
# define SIDE_CLOSED 1
# define SIDE_OUTSIDE 2
# define IMG_FLOOR 0
# define IMG_WALL 1
# define IMG_CLOSED 2
# define IMG_OUTSIDE 3
# define IMG_COLORS 4
# define RGBA_FLOOR 0x505050FF
# define RGBA_WALL 0xE8E8E8FF
# define RGBA_CLOSED 0x262626FF
# define RGBA_OUTSIDE 0x7A5230FF
# define RGBA_BAR_BG 0x202020FF

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

/* Every texture loaded from assets/sprites. */
typedef struct s_textures
{
	mlx_texture_t	*player[DIR_COUNT][SPRITE_FRAMES];
	int				player_frames[DIR_COUNT];
	mlx_texture_t	*exit;
	mlx_texture_t	*broken_sign;
	mlx_texture_t	*facing_wall;
	mlx_texture_t	*glass_down_right;
	mlx_texture_t	*glass_down_left;
	mlx_texture_t	*glass_dark[GLASS_SIDES];
	mlx_texture_t	*glass_grass[GLASS_SIDES];
	mlx_texture_t	*flowerpot;
	mlx_texture_t	*asphalt;
	mlx_texture_t	*grass;
	mlx_texture_t	*tree;
	mlx_texture_t	*lamp;
	mlx_texture_t	*window;
	mlx_texture_t	*shower[DIR_COUNT];
	mlx_texture_t	*desk[DIR_COUNT];
	mlx_texture_t	*table[DIR_COUNT];
	mlx_texture_t	*toilet[DIR_COUNT];
	mlx_texture_t	*lockers[DIR_COUNT];
	mlx_texture_t	*sink[DIR_COUNT];
	mlx_texture_t	*kitchen[DIR_COUNT];
	mlx_texture_t	*coffee[DIR_COUNT];
	mlx_texture_t	*water_cooler[DIR_COUNT];
	mlx_texture_t	*fridge[DIR_COUNT];
	mlx_texture_t	*vending[DIR_COUNT];
}	t_textures;

/* Every MLX image in the window and what is needed to update them. */
typedef struct s_scene
{
	mlx_image_t		*menu[MENU_LINES];
	mlx_texture_t	*cache_tex[IMG_CACHE];
	mlx_image_t		*cache_img[IMG_CACHE];
	int				cache_count;
	mlx_image_t		*color[IMG_COLORS];
	mlx_image_t		*player[DIR_COUNT][SPRITE_FRAMES];
	mlx_image_t		*bar[2];
	int				*sign_instance;
}	t_scene;

/* Per-tile results of the patterns/ rules, computed once at start. */
typedef struct s_layout
{
	bool	*reachable;
	bool	*outside;
	bool	*pots;
	bool	*trees;
	bool	*lamps;
}	t_layout;

/* Top-left tile of the view and the view size in tiles. */
typedef struct s_camera
{
	int	x;
	int	y;
	int	cols;
	int	rows;
}	t_camera;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	int				rows;
	int				cols;
	t_progress		progress;
	t_textures		textures;
	t_scene			scene;
	t_layout		layout;
	t_camera		cam;
	int				player_dir;
	int				player_frame;
	int				move_count;
}	t_game;

/* A yes/no question about one tile, used by the flood fill. */
typedef bool	(*t_tile_test)(t_game *game, int x, int y);

/*
** One flood fill over the map: tiles it may enter (passable), tiles it may
** continue from (spreads, NULL = all), what it has seen and its queue.
*/
typedef struct s_flood
{
	t_game		*game;
	t_tile_test	passable;
	t_tile_test	spreads;
	bool		*seen;
	int			*queue;
	size_t		qend;
}	t_flood;

typedef struct s_map
{
	char	**lines;
	size_t	rows;
	size_t	cols;
	t_point	player;
	int		collectibles;
	int		exits;
}	t_map;

typedef struct s_area
{
	int	right;
	int	top;
	int	bottom;
	int	height;
}	t_area;

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

/* game/game.c */
void			init_game(t_game *game, const char *map_name);

/* game/menu.c */
void			start_map_menu(t_game *game, const char *map_name);

/* game/input.c */
void			move_player(t_game *game, int dx, int dy);
void			key_hook(mlx_key_data_t keydata, void *param);

/* game/error.c */
void			print_error(const char *msg, const char *detail);
int				map_error(const char *msg);
void			fail(t_game *game, const char *msg);

/* game/cleanup.c */
void			free_game(t_game *game);
void			exit_game(t_game *game, int code);

/* map/map_load.c */
char			**load_and_validate(t_game *game, const char *path,
					t_map *parsed);
char			**load_map(t_game *game, const char *name, t_map *parsed);

/* map/map_read.c */
char			**read_map_file(t_game *game, const char *path);

/* map/map.c */
int				validate_map(const t_map *map);
void			free_map(t_map *map);

/* map/flood.c */
bool			flood_init(t_flood *f, t_game *game, t_tile_test passable,
					t_tile_test spreads);
void			flood_add(t_flood *f, int x, int y);
void			flood_spread(t_flood *f, size_t start);
bool			*flood_finish(t_flood *f);

/* map/map_path.c */
bool			*reachable_tiles(t_game *game, t_point start);

/* map/map_path_check.c */
int				path_is_valid(t_game *game, const t_map *parsed);

/* map/map_tile.c */
bool			in_map(t_game *game, int x, int y);
int				tile_index(t_game *game, int x, int y);
char			tile_at(t_game *game, int x, int y);

/* progress/progress.c */
void			init_progress(t_game *game, const t_map *parsed);
bool			is_collected(t_game *game, int x, int y);
void			collect_tile(t_game *game, int x, int y);
uint32_t		progress_color(t_game *game);

/* progress/collectibles.c */
void			pick_collectibles(t_game *game);

/* render/render_init.c */
void			init_render(t_game *game);

/* render/render_map.c */
void			build_scene(t_game *game);
void			render_map(t_game *game);

/* render/render_tiles.c */
void			place_tile(t_game *game, int x, int y);
void			uncover_tile(t_game *game, int x, int y);

/* render/render_images.c */
mlx_image_t		*texture_image(t_game *game, mlx_texture_t *tex);
mlx_image_t		*cached_image(t_game *game, mlx_texture_t *tex);
mlx_image_t		*color_image(t_game *game, uint32_t rgba, uint32_t w,
					uint32_t h);
int				put_image(t_game *game, mlx_image_t *img, int x, int y);

/* render/camera.c */
void			init_camera(t_game *game);
void			update_camera(t_game *game);

/* textures/textures.c */
void			texture_path(char *path, size_t size, const char *dir,
					const char *file);
mlx_texture_t	*load_texture(const char *dir, const char *file);
mlx_texture_t	*load_required_texture(t_game *game, const char *dir,
					const char *file);
void			load_textures(t_game *game);

/* textures/textures_player.c */
void			load_player_textures(t_game *game);

/* textures/textures_furniture.c */
void			load_furniture_textures(t_game *game);

/* textures/textures_glass.c */
void			load_glass_textures(t_game *game);
void			free_glass_textures(t_game *game);

/* textures/textures_free.c */
void			free_textures(t_game *game);

/* patterns/patterns_init.c */
void			init_patterns(t_game *game, const t_map *parsed);

/* patterns/patterns_tile.c */
bool			is_corridor(t_game *game, int x, int y);
mlx_texture_t	*facing_wall_texture(t_game *game, int x, int y);

/* patterns/patterns_collectible.c */
mlx_texture_t	*collectible_tile_texture(t_game *game, int x, int y);

/* patterns/patterns_lines.c */
bool			match_column_texture(t_game *game, int x, int y,
					mlx_texture_t **sprite);
mlx_texture_t	*row_texture(t_game *game, int x, int y);

/* patterns/patterns_runs.c */
bool			is_equipment_run(char first, char last, int length);
mlx_texture_t	*run_texture(t_game *game, t_run run, int face);

/* patterns/patterns_desks.c */
bool			is_sideways_desk(t_game *game, int x, int y);
mlx_texture_t	*empty_table_texture(t_game *game, int x, int y);

/* patterns/patterns_lamp_spot.c */
bool			is_lamp_spot(t_game *game, int x, int y);

/* patterns/patterns_lamps.c */
bool			*lamp_tiles(t_game *game);
mlx_texture_t	*lamp_texture(t_game *game, int x, int y);

/* patterns/patterns_windows.c */
mlx_texture_t	*window_texture(t_game *game, int x, int y);

/* patterns/patterns_glass.c */
mlx_texture_t	*glass_texture(t_game *game, int x, int y, int dx);

/* patterns/patterns_floor.c */
mlx_image_t		*floor_image(t_game *game, int x, int y);
mlx_image_t		*decoration_image(t_game *game, int x, int y);

/* patterns/patterns_outside.c */
bool			*outside_tiles(t_game *game);

/* patterns/patterns_pots.c */
bool			*pot_tiles(t_game *game);

/* patterns/patterns_trees.c */
bool			*tree_tiles(t_game *game);

#endif
