/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_furniture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Loads <name>/down, <name>/up, <name>/left and <name>/right. */
static void	load_faces(mlx_texture_t **tex, const char *name)
{
	tex[DIR_DOWN] = load_texture(name, "down");
	tex[DIR_UP] = load_texture(name, "up");
	tex[DIR_LEFT] = load_texture(name, "left");
	tex[DIR_RIGHT] = load_texture(name, "right");
}

/* Like load_faces, but all four facings must exist. */
static void	load_required_faces(t_game *game, mlx_texture_t **tex,
		const char *name)
{
	int	face;

	load_faces(tex, name);
	face = 0;
	while (face < DIR_COUNT)
	{
		if (!tex[face])
		{
			print_error("failed to load the sprites of", name);
			exit_game(game, 1);
		}
		face++;
	}
}

/* Desks and tables are required; other equipment is optional. */
void	load_furniture_textures(t_game *game)
{
	load_required_faces(game, game->textures.desk, "desk");
	load_required_faces(game, game->textures.table, "table");
	game->textures.shower[DIR_RIGHT] = load_texture("shower", "right");
	game->textures.shower[DIR_LEFT] = load_texture("shower", "left");
	load_faces(game->textures.toilet, "toilet");
	load_faces(game->textures.lockers, "lockers");
	load_faces(game->textures.sink, "sink");
	load_faces(game->textures.kitchen, "kitchen");
	load_faces(game->textures.coffee, "coffee");
	load_faces(game->textures.water_cooler, "water_cooler");
	load_faces(game->textures.fridge, "fridge");
	load_faces(game->textures.vending, "vending_machine");
}
