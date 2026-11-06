/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   game_render.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: akechedz <akechedz@student.42heilbronn.de>#+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/06 17:48:30 by akechedz         #+#    #+#              */
/*   Updated: 2026/11/06 17:49:12 by akechedz        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char	*dir_name(int d)
{
	if (d == DIR_BACK)
		return ("back");
	if (d == DIR_LEFT)
		return ("left");
	if (d == DIR_RIGHT)
		return ("right");
	return ("front");
}

int	tile_color(char tile)
{
	if (tile == '1')
		return (0xE8E8E8);
	if (tile == 'C')
		return (0xFFD700);
	if (tile == 'E')
		return (0x32CD32);
	return (0x505050);
}

static char	*sprite_path(const char *dir_name, int frame)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "%s/%s_%02d.png", SPRITE_DIR, dir_name, frame);
	return (ft_strdup(buf));
}

static void	load_direction_sprites(t_game *game, int d)
{
	int		f;
	char	*path;

	f = 0;
	while (f < SPRITE_FRAMES)
	{
		path = sprite_path(dir_name(d), f + 1);
		if (access(path, F_OK) != 0)
		{
			free(path);
			break ;
		}
		game->player_tex[d][f] = mlx_load_png(path);
		free(path);
		if (!game->player_tex[d][f])
		{
			ft_printf("Error: failed to load player sprite\n");
			exit(1);
		}
		f++;
	}
	game->player_frame_count[d] = f;
	if (f == 0)
	{
		ft_printf("Error: no sprites found for direction '%s'\n",
			dir_name(d));
		exit(1);
	}
}

void	load_player_sprites(t_game *game)
{
	int	d;

	d = 0;
	while (d < DIR_COUNT)
	{
		load_direction_sprites(game, d);
		d++;
	}
}

static uint32_t	blend_pixel(uint8_t *p, uint32_t bg)
{
	uint8_t	a;
	uint8_t	out[3];
	int		i;

	a = p[3];
	if (a == 255)
		return (((uint32_t) p[0] << 24) | ((uint32_t) p[1] << 16)
			| ((uint32_t) p[2] << 8) | 0xFF);
	i = 0;
	while (i < 3)
	{
		out[i] = (uint8_t)(((int) p[i] * a
					+(int)((bg >> (24 - i * 8)) & 0xFF) * (255 - a)) / 255);
		i++;
	}
	return (((uint32_t) out[0] << 24) | ((uint32_t) out[1] << 16)
		| ((uint32_t) out[2] << 8) | 0xFF);
}

static uint32_t	texture_pixel(mlx_texture_t *tex, int i, int j, uint32_t bg)
{
	int	size;
	int	sx;
	int	sy;

	size = (int) tex->width;
	if ((int) tex->height > size)
		size = (int) tex->height;
	sx = j * size / TILE_SIZE - (size - (int) tex->width) / 2;
	sy = i * size / TILE_SIZE - (size - (int) tex->height) / 2;
	if (sx < 0 || sx >= (int) tex->width || sy < 0 || sy >= (int) tex->height)
		return (bg);
	return (blend_pixel(tex->pixels + ((size_t) sy * tex->width + sx) * 4, bg));
}

/*
** Draws layers[1] over bg at tile pos. If layers[0] is set, it is drawn between
** the two.
*/
static void	draw_texture_tile(t_game *game, mlx_texture_t *layers[2],
	t_point pos, uint32_t bg)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			color = bg;
			if (layers[0])
				color = texture_pixel(layers[0], i, j, bg);
			mlx_put_pixel(game->img, pos.x * TILE_SIZE + j, SCORE_BAR_HEIGHT + pos.y * TILE_SIZE + i, texture_pixel(layers[1], i, j, color));
			j++;
		}
		i++;
	}
}

void	draw_player_tile(t_game *game, int x, int y)
{
	mlx_texture_t	*layers[2];
	int				frame_idx;
	char			tile;

	frame_idx = game->player_frame
		% game->player_frame_count[game->player_dir];
	layers[1] = game->player_tex[game->player_dir][frame_idx];
	layers[0] = NULL;
	tile = '0';
	if (is_collected(game, game->cam_x + x, game->cam_y + y))
	{
		layers[0] = collectible_tile_texture(game, game->cam_x + x,
				game->cam_y + y);
		if (!layers[0])
			tile = 'C';
	}
	draw_texture_tile(game, layers, (t_point){x, y},
		((uint32_t) tile_color(tile) << 8) | 0xFF);
}

void	load_exit_sprite(t_game *game)
{
	game->exit_tex = mlx_load_png(EXIT_SPRITE_PATH);
	if (!game->exit_tex)
	{
		ft_printf("Error: failed to load exit sprite\n");
		exit(1);
	}
}

void	draw_exit_tile(t_game *game, int x, int y)
{
	mlx_texture_t	*layers[2];

	layers[0] = NULL;
	layers[1] = game->exit_tex;
	draw_texture_tile(game, layers, (t_point){x, y},
		((uint32_t) tile_color('0') << 8) | 0xFF);
}

void	draw_tile(t_game *game, int x, int y, int color)
{
	int			i;
	int			j;
	uint32_t	rgba;

	rgba = ((uint32_t) color << 8) | 0xFF;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(game->img, x * TILE_SIZE + j,
				SCORE_BAR_HEIGHT + y * TILE_SIZE + i, rgba);
			j++;
		}
		i++;
	}
}

/*
** A collected task shows its sprite. One still to do shows the broken sign over
** its sprite. Without a sprite it is a plain coloured tile.
*/
static void	draw_collectible_tile(t_game *game, t_point pos, int mx, int my)
{
	mlx_texture_t	*sprite;
	mlx_texture_t	*layers[2];
	bool			collected;

	sprite = collectible_tile_texture(game, mx, my);
	collected = is_collected(game, mx, my);
	layers[0] = NULL;
	layers[1] = sprite;
	if (!collected)
	{
		layers[0] = sprite;
		layers[1] = game->broken_sign_tex;
	}
	if (sprite)
		draw_texture_tile(game, layers, pos,
			((uint32_t) tile_color('0') << 8) | 0xFF);
	else if (collected)
		draw_tile(game, pos.x, pos.y, tile_color('1'));
	else
		draw_tile(game, pos.x, pos.y, tile_color('C'));
}

static void	draw_wall_tile(t_game *game, t_point pos, int mx, int my)
{
	mlx_texture_t	*layers[2];

	layers[0] = NULL;
	layers[1] = empty_table_texture(game, mx, my);
	if (!layers[1])
		layers[1] = facing_wall_texture(game, mx, my);
	if (layers[1])
		draw_texture_tile(game, layers, pos,
			((uint32_t) tile_color('0') << 8) | 0xFF);
	else
		draw_tile(game, pos.x, pos.y, tile_color('1'));
}

/* The strip above the map: empty at the start, full when all tasks are collected. */

static void	draw_score_bar(t_game *game)
{
	int	width;
	int	filled;
	int	x;
	int	y;

	width = game->view_cols * TILE_SIZE - 2 * SCORE_BAR_BORDER;
	filled = width * (game->progress.collectibles_total
			-game->progress.collectibles_left)
		/ game->progress.collectibles_total;
	y = -1;
	while (++y < SCORE_BAR_HEIGHT)
	{
		x = -1;
		while (++x < game->view_cols * TILE_SIZE)
		{
			if (y >= SCORE_BAR_BORDER && y < SCORE_BAR_HEIGHT - SCORE_BAR_BORDER
				&& x >= SCORE_BAR_BORDER && x < SCORE_BAR_BORDER + filled)
				mlx_put_pixel(game->img, x, y, 0xFFD700FF);
			else
				mlx_put_pixel(game->img, x, y, 0x202020FF);
		}
	}
}

/* Draws the map tile shown at screen tile (x, y). */
static void	draw_map_tile(t_game *game, int x, int y)
{
	int	mx;
	int	my;

	mx = game->cam_x + x;
	my = game->cam_y + y;
	if (mx == game->progress.player.x && my == game->progress.player.y)
		draw_player_tile(game, x, y);
	else if (game->map[my][mx] == 'E')
		draw_exit_tile(game, x, y);
	else if (game->map[my][mx] == 'C')
		draw_collectible_tile(game, (t_point){x, y}, mx, my);
	else if (game->map[my][mx] == '1')
		draw_wall_tile(game, (t_point){x, y}, mx, my);
	else
		draw_tile(game, x, y, tile_color(game->map[my][mx]));
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	update_camera(game);
	draw_score_bar(game);
	y = 0;
	while (y < game->view_rows)
	{
		x = 0;
		while (x < game->view_cols)
		{
			draw_map_tile(game, x, y);
			x++;
		}
		y++;
	}
}
