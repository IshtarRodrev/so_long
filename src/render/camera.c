/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:22:44 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 04:44:38 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	clamp_camera(t_game *game)
{
	int	max_cam_x;
	int	max_cam_y;

	max_cam_x = game->cols - game->view_cols;
	max_cam_y = game->rows - game->view_rows;
	if (game->cam_x < 0)
		game->cam_x = 0;
	if (game->cam_y < 0)
		game->cam_y = 0;
	if (game->cam_x > max_cam_x)
		game->cam_x = max_cam_x;
	if (game->cam_y > max_cam_y)
		game->cam_y = max_cam_y;
}

/* Scrolls so the player stays at least CAMERA_MARGIN tiles from the edges. */
static void	follow_player(t_game *game)
{
	int	px;
	int	py;

	px = game->progress.player.x;
	py = game->progress.player.y;
	if (px - game->cam_x < CAMERA_MARGIN)
		game->cam_x = px - CAMERA_MARGIN;
	else if (px - game->cam_x > game->view_cols - 1 - CAMERA_MARGIN)
		game->cam_x = px - (game->view_cols - 1 - CAMERA_MARGIN);
	if (py - game->cam_y < CAMERA_MARGIN)
		game->cam_y = py - CAMERA_MARGIN;
	else if (py - game->cam_y > game->view_rows - 1 - CAMERA_MARGIN)
		game->cam_y = py - (game->view_rows - 1 - CAMERA_MARGIN);
}

/* Moves every instance of img by (dx, dy) tiles. */
static void	shift_image(mlx_image_t *img, int dx, int dy)
{
	size_t	i;

	i = 0;
	while (i < img->count)
	{
		img->instances[i].x += dx * TILE_SIZE;
		img->instances[i].y += dy * TILE_SIZE;
		i++;
	}
}

void	init_camera(t_game *game)
{
	game->view_cols = VIEWPORT_COLS;
	if (game->cols < VIEWPORT_COLS)
		game->view_cols = game->cols;
	game->view_rows = VIEWPORT_ROWS;
	if (game->rows < VIEWPORT_ROWS)
		game->view_rows = game->rows;
	game->cam_x = game->progress.player.x - game->view_cols / 2;
	game->cam_y = game->progress.player.y - game->view_rows / 2;
	clamp_camera(game);
}

/* Follows the player and moves the map images if the view scrolled. */
void	update_camera(t_game *game)
{
	int	old_x;
	int	old_y;
	int	i;

	old_x = game->cam_x;
	old_y = game->cam_y;
	follow_player(game);
	clamp_camera(game);
	if (old_x == game->cam_x && old_y == game->cam_y)
		return ;
	i = -1;
	while (++i < game->cache_count)
		shift_image(game->cache_img[i], old_x - game->cam_x,
			old_y - game->cam_y);
	i = -1;
	while (++i < IMG_COLORS)
		shift_image(game->color_img[i], old_x - game->cam_x,
			old_y - game->cam_y);
}
