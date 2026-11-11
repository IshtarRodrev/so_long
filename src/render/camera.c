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

	max_cam_x = game->cols - game->cam.cols;
	max_cam_y = game->rows - game->cam.rows;
	if (game->cam.x < 0)
		game->cam.x = 0;
	if (game->cam.y < 0)
		game->cam.y = 0;
	if (game->cam.x > max_cam_x)
		game->cam.x = max_cam_x;
	if (game->cam.y > max_cam_y)
		game->cam.y = max_cam_y;
}

/* Scrolls so the player stays at least CAMERA_MARGIN tiles from the edges. */
static void	follow_player(t_game *game)
{
	int	px;
	int	py;

	px = game->progress.player.x;
	py = game->progress.player.y;
	if (px - game->cam.x < CAMERA_MARGIN)
		game->cam.x = px - CAMERA_MARGIN;
	else if (px - game->cam.x > game->cam.cols - 1 - CAMERA_MARGIN)
		game->cam.x = px - (game->cam.cols - 1 - CAMERA_MARGIN);
	if (py - game->cam.y < CAMERA_MARGIN)
		game->cam.y = py - CAMERA_MARGIN;
	else if (py - game->cam.y > game->cam.rows - 1 - CAMERA_MARGIN)
		game->cam.y = py - (game->cam.rows - 1 - CAMERA_MARGIN);
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
	game->cam.cols = VIEWPORT_COLS;
	if (game->cols < VIEWPORT_COLS)
		game->cam.cols = game->cols;
	game->cam.rows = VIEWPORT_ROWS;
	if (game->rows < VIEWPORT_ROWS)
		game->cam.rows = game->rows;
	game->cam.x = game->progress.player.x - game->cam.cols / 2;
	game->cam.y = game->progress.player.y - game->cam.rows / 2;
	clamp_camera(game);
}

/* Follows the player and moves the map images if the view scrolled. */
void	update_camera(t_game *game)
{
	int	old_x;
	int	old_y;
	int	i;

	old_x = game->cam.x;
	old_y = game->cam.y;
	follow_player(game);
	clamp_camera(game);
	if (old_x == game->cam.x && old_y == game->cam.y)
		return ;
	i = -1;
	while (++i < game->scene.cache_count)
		shift_image(game->scene.cache_img[i], old_x - game->cam.x,
			old_y - game->cam.y);
	i = -1;
	while (++i < IMG_COLORS)
		shift_image(game->scene.color[i], old_x - game->cam.x,
			old_y - game->cam.y);
}
