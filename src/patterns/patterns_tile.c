/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_tile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 20:33:24 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* True if (x, y) is a floor tile with walls above and below it. */

bool	is_corridor(t_game *game, int x, int y)
{
	return (tile_at(game, x, y) == '0' && tile_at(game, x, y - 1) == '1'
		&& tile_at(game, x, y + 1) == '1');
}

/* True if the walls at (x, y) and (x + dx, y + 1)
touch only at a corner.*/

static bool	diagonal_step(t_game *game, int x, int y, int dx)
{
	return (tile_at(game, x, y) == '1'
		&& tile_at(game, x + dx, y + 1) == '1'
		&& tile_at(game, x + dx, y) != '1'
		&& tile_at(game, x, y + 1) != '1');
}

/*
** How many walls the diagonal chain through the wall at (x, y) has. It runs
** down to the right if dx is 1, and down to the left if dx is -1.
*/

static int	diagonal_length(t_game *game, int x, int y, int dx)
{
	int	length;
	int	cx;
	int	cy;

	length = 1;
	cx = x;
	cy = y;
	while (diagonal_step(game, cx, cy, dx))
	{
		length++;
		cx += dx;
		cy++;
	}
	cx = x;
	cy = y;
	while (diagonal_step(game, cx - dx, cy - 1, dx))
	{
		length++;
		cx -= dx;
		cy--;
	}
	return (length);
}

/*
** Returns the sprite for a wall that is glass fence or faces the camera, or NULL
** for other walls and for walls whose sprite file is missing.
** Glass fence: more than 3 walls in a diagonal chain, touching only at corners.
** Facing the camera: floor, a collectible or the exit below it.
*/

mlx_texture_t	*facing_wall_texture(t_game *game, int x, int y)
{
	char	below;

	if (game->textures.glass_down_right && diagonal_length(game, x, y, 1) > 3)
		return (glass_texture(game, x, y, 1));
	if (game->textures.glass_down_left && diagonal_length(game, x, y, -1) > 3)
		return (glass_texture(game, x, y, -1));
	below = tile_at(game, x, y + 1);
	if (below == '0' || below == 'C' || below == 'E')
		return (game->textures.facing_wall);
	return (NULL);
}
