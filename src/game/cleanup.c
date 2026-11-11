/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

/* Frees the per-tile arrays built at start (progress and decorations). */
static void	free_tile_data(t_game *game)
{
	free(game->progress.collected);
	game->progress.collected = NULL;
	free(game->scene.sign_instance);
	game->scene.sign_instance = NULL;
	free(game->layout.reachable);
	game->layout.reachable = NULL;
	free(game->layout.outside);
	game->layout.outside = NULL;
	free(game->layout.pots);
	game->layout.pots = NULL;
	free(game->layout.trees);
	game->layout.trees = NULL;
	free(game->layout.lamps);
	game->layout.lamps = NULL;
}

/*
** Frees everything the game allocated. Safe to call at any point: parts that
** were never allocated are NULL and skipped. mlx_terminate also deletes every
** image and closes the window.
*/
void	free_game(t_game *game)
{
	int	row;

	if (game->map)
	{
		row = 0;
		while (row < game->rows)
			free(game->map[row++]);
		free(game->map);
		game->map = NULL;
	}
	free_tile_data(game);
	free_textures(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->mlx = NULL;
}

/* Frees everything and ends the program with code. */
void	exit_game(t_game *game, int code)
{
	free_game(game);
	exit(code);
}
