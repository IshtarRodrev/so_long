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
# define MENU_WIN_W 1200
# define MENU_WIN_H 800
# define VIEWPORT_COLS 30
# define VIEWPORT_ROWS 20
# define CAMERA_MARGIN 5
# define MENU_LINES 2
# define MAPS_DIR "maps"
# define SPRITE_DIR "assets/sprites"
# define EXIT_SPRITE_PATH "assets/sprites/exit_tile.png"
# define BROKEN_SIGN_SPRITE_PATH "assets/sprites/broken_sign_tile.png"
# define WALL_DOWN_SPRITE_PATH "assets/sprites/wall_down.png"
# define SHOWER_RIGHT_SPRITE_PATH "assets/sprites/shower_right.png"
# define SHOWER_LEFT_SPRITE_PATH "assets/sprites/shower_left.png"
# define GLASS_DR_SPRITE_PATH "assets/sprites/glass_fence_down_right.png"
# define GLASS_DL_SPRITE_PATH "assets/sprites/glass_fence_down_left.png"
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
# define IMG_CACHE 96
# define IMG_FLOOR 0
# define IMG_WALL 1
# define IMG_TODO 2
# define IMG_COLORS 3
# define RGBA_FLOOR 0x505050FF
# define RGBA_WALL 0xE8E8E8FF
# define RGBA_TODO 0xFFD700FF
# define RGBA_BAR_BG 0x202020FF
# define RGBA_BAR_FILL 0xFFD700FF

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
	mlx_texture_t	*cache_tex[IMG_CACHE];
	mlx_image_t		*cache_img[IMG_CACHE];
	int				cache_count;
	mlx_image_t		*color_img[IMG_COLORS];
	mlx_image_t		*player_img[DIR_COUNT][SPRITE_FRAMES];
	mlx_image_t		*bar_img[2];
	int				*cover;
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
void			init_game(t_game *game, const char *map_name);

/* menu.c */
void			start_map_menu(t_game *game, const char *map_name);

/* map/map.c */
char			*read_file_to_string(const char *path);
int				parse_map_file(const char *path, t_map *map);
int				validate_map(const t_map *map);
void			free_map(t_map *map);

/* map/map_path.c */
void			search_from_player(t_path_search *s);
int				collectible_is_trapped(t_path_search *s);

/* map/map_path_check.c */
void			print_error(const char *msg, const char *detail);
int				map_error(const char *msg);
int				path_is_valid(const t_map *map);

/* map/map_read.c */
char			**read_map_file(t_game *game, const char *path);

/* map/params.c */
char			**load_and_validate(t_game *game, const char *path, t_lay *lay);
char			**load_map_by_name(t_game *game, const char *map_name,
					t_lay *lay);

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
mlx_image_t		*texture_image(t_game *game, mlx_texture_t *tex);
mlx_image_t		*image_for(t_game *game, mlx_texture_t *tex);
mlx_image_t		*color_image(t_game *game, uint32_t rgba, uint32_t w,
					uint32_t h);
int				put_image(t_game *game, mlx_image_t *img, int x, int y);
void			load_exit_sprite(t_game *game);

/* game_render_tiles.c */
void			place_tile(t_game *game, int mx, int my);
void			uncover_tile(t_game *game, int mx, int my);

/* game_render_map.c */
void			build_scene(t_game *game);
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
