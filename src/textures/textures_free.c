/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

/* Deletes the furniture textures (every facing of every object). */
static void	free_furniture_textures(t_game *game)
{
	delete_textures(game->textures.shower, DIR_COUNT);
	delete_textures(game->textures.desk, DIR_COUNT);
	delete_textures(game->textures.table, DIR_COUNT);
	delete_textures(game->textures.toilet, DIR_COUNT);
	delete_textures(game->textures.lockers, DIR_COUNT);
	delete_textures(game->textures.sink, DIR_COUNT);
	delete_textures(game->textures.kitchen, DIR_COUNT);
	delete_textures(game->textures.coffee, DIR_COUNT);
	delete_textures(game->textures.water_cooler, DIR_COUNT);
	delete_textures(game->textures.fridge, DIR_COUNT);
	delete_textures(game->textures.vending, DIR_COUNT);
}

/* Deletes every loaded sprite (textures; images belong to MLX). */
void	free_textures(t_game *game)
{
	int	d;

	d = 0;
	while (d < DIR_COUNT)
		delete_textures(game->textures.player[d++], SPRITE_FRAMES);
	delete_textures(&game->textures.exit, 1);
	delete_textures(&game->textures.broken_sign, 1);
	delete_textures(&game->textures.facing_wall, 1);
	free_glass_textures(game);
	delete_textures(&game->textures.flowerpot, 1);
	delete_textures(&game->textures.asphalt, 1);
	delete_textures(&game->textures.grass, 1);
	delete_textures(&game->textures.tree, 1);
	delete_textures(&game->textures.lamp, 1);
	delete_textures(&game->textures.window, 1);
	free_furniture_textures(game);
}
