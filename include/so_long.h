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
# define MENU_LINES 2
# define MAPS_DIR "maps"
# define SPRITE_DIR "assets/sprites"
# define EXIT_SPRITE_PATH "assets/sprites/exit/tile.png"
# define BROKEN_SIGN_SPRITE_PATH "assets/sprites/broken_sign/tile.png"
# define WALL_DOWN_SPRITE_PATH "assets/sprites/wall/down.png"
# define SHOWER_RIGHT_SPRITE_PATH "assets/sprites/shower/right.png"
# define SHOWER_LEFT_SPRITE_PATH "assets/sprites/shower/left.png"
# define GLASS_DR_SPRITE_PATH "assets/sprites/glass_fence/down_right.png"
# define GLASS_DL_SPRITE_PATH "assets/sprites/glass_fence/down_left.png"
# define FLOWERPOT_SPRITE_PATH "assets/sprites/flowerpot/tile.png"
# define ASPHALT_SPRITE_PATH "assets/sprites/asphalt/tile.png"
# define GRASS_SPRITE_PATH "assets/sprites/grass/tile.png"
# define TREE_SPRITE_PATH "assets/sprites/tree/tile.png"
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

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	int				rows;
	int				cols;
	mlx_image_t		*menu_imgs[MENU_LINES];
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
	mlx_texture_t	*glass_dark_tex[GLASS_SIDES];
	mlx_texture_t	*glass_grass_tex[GLASS_SIDES];
	mlx_texture_t	*flowerpot_tex;
	mlx_texture_t	*asphalt_tex;
	mlx_texture_t	*grass_tex;
	mlx_texture_t	*tree_tex;
	mlx_texture_t	*shower_tex[DIR_COUNT];
	mlx_texture_t	*desk_tex[DIR_COUNT];
	mlx_texture_t	*table_tex[DIR_COUNT];
	mlx_texture_t	*toilet_tex[DIR_COUNT];
	mlx_texture_t	*lockers_tex[DIR_COUNT];
	mlx_texture_t	*sink_tex[DIR_COUNT];
	mlx_texture_t	*kitchen_tex[DIR_COUNT];
	mlx_texture_t	*coffee_tex[DIR_COUNT];
	mlx_texture_t	*water_cooler_tex[DIR_COUNT];
	mlx_texture_t	*fridge_tex[DIR_COUNT];
	mlx_texture_t	*vending_tex[DIR_COUNT];
	mlx_texture_t	*cache_tex[IMG_CACHE];
	mlx_image_t		*cache_img[IMG_CACHE];
	int				cache_count;
	mlx_image_t		*color_img[IMG_COLORS];
	mlx_image_t		*player_img[DIR_COUNT][SPRITE_FRAMES];
	mlx_image_t		*bar_img[2];
	int				*sign_instance;
	bool			*reachable;
	bool			*outside;
	bool			*pots;
	bool			*trees;
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

typedef struct s_fill
{
	const t_map	*map;
	const bool	*reachable;
	bool		*outside;
	int			*queue;
	size_t		qend;
}	t_fill;

typedef struct s_pot_fill
{
	t_game		*game;
	bool		*seen;
	bool		*pots;
	int			*queue;
	size_t		qend;
}	t_pot_fill;

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
char			**load_and_validate(t_game *game, const char *path, t_map *lay);
char			**load_map(t_game *game, const char *name, t_map *lay);

/* map/map_read.c */
char			**read_map_file(t_game *game, const char *path);

/* map/map.c */
int				validate_map(const t_map *map);
void			free_map(t_map *map);

/* map/map_path.c */
void			search_from_player(t_path_search *s);

/* map/map_path_check.c */
int				path_is_valid(const t_map *map);
bool			*reachable_tiles(const t_map *map);

/* map/map_tile.c */
bool			in_map(t_game *game, int x, int y);
int				tile_index(t_game *game, int x, int y);
char			tile_at(t_game *game, int mx, int my);

/* progress/progress.c */
void			init_progress(t_game *game, const t_map *lay);
bool			is_collected(t_game *game, int mx, int my);
void			collect_tile(t_game *game, int mx, int my);
uint32_t		progress_color(t_game *game);

/* progress/collectibles.c */
void			pick_collectibles(t_game *game);

/* render/render_init.c */
void			init_render(t_game *game);

/* render/render_map.c */
void			build_scene(t_game *game);
void			render_map(t_game *game);

/* render/render_tiles.c */
void			place_tile(t_game *game, int mx, int my);
void			uncover_tile(t_game *game, int mx, int my);

/* render/render_images.c */
mlx_image_t		*texture_image(t_game *game, mlx_texture_t *tex);
mlx_image_t		*cached_image(t_game *game, mlx_texture_t *tex);
mlx_image_t		*color_image(t_game *game, uint32_t rgba, uint32_t w,
					uint32_t h);
int				put_image(t_game *game, mlx_image_t *img, int x, int y);
void			load_exit_sprite(t_game *game);

/* render/camera.c */
void			init_camera(t_game *game);
void			update_camera(t_game *game);

/* sprites/sprites_player.c */
void			load_player_sprites(t_game *game);

/* patterns/patterns_init.c */
void			init_patterns(t_game *game, const t_map *lay);

/* patterns/patterns.c */
void			load_pattern_sprites(t_game *game);

/* patterns/patterns_glass_sprites.c */
void			load_glass_sprites(t_game *game);
void			free_glass_sprites(t_game *game);

/* patterns/patterns_tile.c */
bool			is_corridor(t_game *game, int mx, int my);
mlx_texture_t	*facing_wall_texture(t_game *game, int mx, int my);

/* patterns/patterns_collectible.c */
mlx_texture_t	*collectible_tile_texture(t_game *game, int mx, int my);

/* patterns/patterns_lines.c */
bool			match_column_texture(t_game *game, int mx, int my,
					mlx_texture_t **sprite);
mlx_texture_t	*row_texture(t_game *game, int mx, int my);

/* patterns/patterns_runs.c */
bool			is_equipment_run(char first, char last, int length);
mlx_texture_t	*run_texture(t_game *game, t_run run, int face);

/* patterns/patterns_desks.c */
bool			is_sideways_desk(t_game *game, int mx, int my);
mlx_texture_t	*empty_table_texture(t_game *game, int mx, int my);

/* patterns/patterns_glass.c */
mlx_texture_t	*glass_texture(t_game *game, int mx, int my, int dx);

/* patterns/patterns_floor.c */
mlx_image_t		*floor_image(t_game *game, int mx, int my);
mlx_image_t		*decoration_image(t_game *game, int mx, int my);

/* patterns/patterns_outside.c */
bool			*outside_tiles(const t_map *map, const bool *reachable);

/* patterns/patterns_areas.c */
void			add_area_tile(t_pot_fill *f, int x, int y);
void			fill_area(t_pot_fill *f, size_t start);

/* patterns/patterns_pots.c */
bool			*pot_tiles(t_game *game);

/* patterns/patterns_trees.c */
bool			*tree_tiles(t_game *game);

#endif
