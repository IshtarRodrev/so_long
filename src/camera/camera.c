/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:22:44 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:05 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	compute_viewport_size(t_game *game)
{
	game->view_cols = VIEWPORT_COLS;
	if (game->cols < VIEWPORT_COLS)
		game->view_cols = game->cols;
	game->view_rows = VIEWPORT_ROWS;
	if (game->rows < VIEWPORT_ROWS)
		game->view_rows = game->rows;
}

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

void	init_camera(t_game *game)
{
	int	px;
	int	py;

	px = game->progress.player.x;
	py = game->progress.player.y;
	compute_viewport_size(game);
	game->cam_x = px - game->view_cols / 2;
	game->cam_y = py - game->view_rows / 2;
	clamp_camera(game);
}

void	update_camera(t_game *game)
{
	int	px;
	int	py;

	px = game->progress.player.x;
	py = game->progress.player.y;
	compute_viewport_size(game);
	if (px - game->cam_x < CAMERA_MARGIN)
		game->cam_x = px - CAMERA_MARGIN;
	else if (px - game->cam_x > game->view_cols - 1 - CAMERA_MARGIN)
		game->cam_x = px - (game->view_cols - 1 - CAMERA_MARGIN);
	if (py - game->cam_y < CAMERA_MARGIN)
		game->cam_y = py - CAMERA_MARGIN;
	else if (py - game->cam_y > game->view_rows - 1 - CAMERA_MARGIN)
		game->cam_y = py - (game->view_rows - 1 - CAMERA_MARGIN);
	clamp_camera(game);
}
