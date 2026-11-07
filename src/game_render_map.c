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

/* One hidden instance per player frame, on top of the map. */
static void	place_player(t_game *game)
{
	int	d;
	int	f;

	d = 0;
	while (d < DIR_COUNT)
	{
		f = 0;
		while (f < game->player_frame_count[d])
		{
			game->player_img[d][f] = texture_image(game,
					game->player_tex[d][f]);
			put_image(game, game->player_img[d][f], 0, 0);
			game->player_img[d][f]->instances[0].enabled = false;
			f++;
		}
		d++;
	}
}

/* Shows only the current player frame, at the player's tile. */
static void	update_player(t_game *game)
{
	mlx_image_t	*img;
	int			d;
	int			f;

	d = -1;
	while (++d < DIR_COUNT)
	{
		f = -1;
		while (++f < game->player_frame_count[d])
			game->player_img[d][f]->instances[0].enabled = false;
	}
	d = game->player_dir;
	img = game->player_img[d][game->player_frame
		% game->player_frame_count[d]];
	img->instances[0].x = (game->progress.player.x - game->cam_x) * TILE_SIZE
		+ (TILE_SIZE - (int) img->width) / 2;
	img->instances[0].y = SCORE_BAR_HEIGHT + (game->progress.player.y
			- game->cam_y) * TILE_SIZE + (TILE_SIZE - (int) img->height) / 2;
	img->instances[0].enabled = true;
}

/* The bar above the map: empty at the start, full when all tasks are done. */
static void	update_score_bar(t_game *game)
{
	int	width;
	int	filled;

	width = game->view_cols * TILE_SIZE - 2 * SCORE_BAR_BORDER;
	filled = width * (game->progress.collectibles_total
			- game->progress.collectibles_left)
		/ game->progress.collectibles_total;
	if (filled <= 0)
	{
		game->bar_img[1]->instances[0].enabled = false;
		return ;
	}
	if (!mlx_resize_image(game->bar_img[1], filled,
			SCORE_BAR_HEIGHT - 2 * SCORE_BAR_BORDER))
	{
		print_error("failed to resize score bar", NULL);
		exit_game(game, 1);
	}
	game->bar_img[1]->instances[0].enabled = true;
}

/* Puts every map tile, the player and the score bar in the window, once. */
void	build_scene(t_game *game)
{
	int	mx;
	int	my;

	game->color_img[IMG_FLOOR] = color_image(game, RGBA_FLOOR, TILE_SIZE,
			TILE_SIZE);
	game->color_img[IMG_WALL] = color_image(game, RGBA_WALL, TILE_SIZE,
			TILE_SIZE);
	game->color_img[IMG_TODO] = color_image(game, RGBA_TODO, TILE_SIZE,
			TILE_SIZE);
	my = -1;
	while (++my < game->rows)
	{
		mx = -1;
		while (++mx < game->cols)
			place_tile(game, mx, my);
	}
	place_player(game);
	game->bar_img[0] = color_image(game, RGBA_BAR_BG,
			game->view_cols * TILE_SIZE, SCORE_BAR_HEIGHT);
	put_image(game, game->bar_img[0], 0, 0);
	game->bar_img[1] = color_image(game, RGBA_BAR_FILL, 1,
			SCORE_BAR_HEIGHT - 2 * SCORE_BAR_BORDER);
	put_image(game, game->bar_img[1], SCORE_BAR_BORDER, SCORE_BAR_BORDER);
	render_map(game);
}

void	render_map(t_game *game)
{
	update_camera(game);
	update_player(game);
	update_score_bar(game);
}
