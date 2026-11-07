/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
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
		while (f < game->textures.player_frames[d])
		{
			game->scene.player[d][f] = texture_image(game,
					game->textures.player[d][f]);
			put_image(game, game->scene.player[d][f], 0, 0);
			game->scene.player[d][f]->instances[0].enabled = false;
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
		while (++f < game->textures.player_frames[d])
			game->scene.player[d][f]->instances[0].enabled = false;
	}
	d = game->player_dir;
	img = game->scene.player[d][game->player_frame
		% game->textures.player_frames[d]];
	img->instances[0].x = (game->progress.player.x - game->cam.x) * TILE_SIZE
		+ (TILE_SIZE - (int) img->width) / 2;
	img->instances[0].y = SCORE_BAR_HEIGHT + (game->progress.player.y
			- game->cam.y) * TILE_SIZE + (TILE_SIZE - (int) img->height) / 2;
	img->instances[0].enabled = true;
}

/*
** The bar above the map: empty at the start, full when all tasks are done.
** Its colour goes from red through orange and yellow to green: the 1x1 image
** is shrunk back to one pixel, recoloured, and stretched to the new width.
*/
static void	update_score_bar(t_game *game)
{
	mlx_image_t	*bar;
	int			filled;
	bool		ok;

	bar = game->scene.bar[1];
	filled = (game->cam.cols * TILE_SIZE - 2 * SCORE_BAR_BORDER)
		* (game->progress.collectibles_total - game->progress.collectibles_left)
		/ game->progress.collectibles_total;
	bar->instances[0].enabled = (filled > 0);
	if (filled <= 0)
		return ;
	ok = mlx_resize_image(bar, 1, 1);
	if (ok)
	{
		mlx_put_pixel(bar, 0, 0, progress_color(game));
		ok = mlx_resize_image(bar, filled,
				SCORE_BAR_HEIGHT - 2 * SCORE_BAR_BORDER);
	}
	if (!ok)
		fail(game, "failed to resize score bar");
}

/* Puts every map tile, the player and the score bar in the window, once. */
void	build_scene(t_game *game)
{
	int	mx;
	int	my;

	init_render(game);
	my = -1;
	while (++my < game->rows)
	{
		mx = -1;
		while (++mx < game->cols)
			place_tile(game, mx, my);
	}
	place_player(game);
	game->scene.bar[0] = color_image(game, RGBA_BAR_BG,
			game->cam.cols * TILE_SIZE, SCORE_BAR_HEIGHT);
	put_image(game, game->scene.bar[0], 0, 0);
	game->scene.bar[1] = color_image(game, RGBA_BAR_BG, 1,
			SCORE_BAR_HEIGHT - 2 * SCORE_BAR_BORDER);
	put_image(game, game->scene.bar[1], SCORE_BAR_BORDER, SCORE_BAR_BORDER);
	render_map(game);
}

void	render_map(t_game *game)
{
	update_camera(game);
	update_player(game);
	update_score_bar(game);
}
