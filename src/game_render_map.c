/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:48:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 20:49:09 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

/*The bar above the map: empty at the start, full when all tasks are collected*/

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
