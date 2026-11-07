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

/* Deletes the count textures of tex that were loaded and clears them. */
static void	delete_textures(mlx_texture_t **tex, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (tex[i])
			mlx_delete_texture(tex[i]);
		tex[i] = NULL;
		i++;
	}
}

static void	free_sprites(t_game *game)
{
	int	d;

	d = 0;
	while (d < DIR_COUNT)
		delete_textures(game->player_tex[d++], SPRITE_FRAMES);
	delete_textures(&game->exit_tex, 1);
	delete_textures(&game->broken_sign_tex, 1);
	delete_textures(&game->facing_wall_tex, 1);
	free_glass_sprites(game);
	delete_textures(&game->flowerpot_tex, 1);
	delete_textures(&game->asphalt_tex, 1);
	delete_textures(&game->grass_tex, 1);
	delete_textures(&game->tree_tex, 1);
	delete_textures(game->shower_tex, DIR_COUNT);
	delete_textures(game->desk_tex, DIR_COUNT);
	delete_textures(game->table_tex, DIR_COUNT);
	delete_textures(game->toilet_tex, DIR_COUNT);
	delete_textures(game->lockers_tex, DIR_COUNT);
	delete_textures(game->sink_tex, DIR_COUNT);
	delete_textures(game->kitchen_tex, DIR_COUNT);
	delete_textures(game->coffee_tex, DIR_COUNT);
	delete_textures(game->water_cooler_tex, DIR_COUNT);
	delete_textures(game->fridge_tex, DIR_COUNT);
	delete_textures(game->vending_tex, DIR_COUNT);
}

/* Frees the per-tile arrays built at start (progress and decorations). */
static void	free_tile_data(t_game *game)
{
	free(game->progress.collected);
	game->progress.collected = NULL;
	free(game->sign_instance);
	game->sign_instance = NULL;
	free(game->reachable);
	game->reachable = NULL;
	free(game->outside);
	game->outside = NULL;
	free(game->pots);
	game->pots = NULL;
	free(game->trees);
	game->trees = NULL;
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
	free_sprites(game);
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
