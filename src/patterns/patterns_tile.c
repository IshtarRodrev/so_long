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

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/* The player's starting tile ('P') is floor. */

char	tile_at(t_game *game, int mx, int my)
{
	if (my < 0 || my >= game->rows || mx < 0 || mx >= game->cols)
		return ('\0');
	if (game->map[my][mx] == 'P')
		return ('0');
	return (game->map[my][mx]);
}

/* True if (mx, my) is a floor tile with walls above and below it. */

bool	is_corridor(t_game *game, int mx, int my)
{
	return (tile_at(game, mx, my) == '0' && tile_at(game, mx, my - 1) == '1'
		&& tile_at(game, mx, my + 1) == '1');
}

/* True if the walls at (mx, my) and (mx + dx, my + 1)
touch only at a corner.*/

static bool	diagonal_step(t_game *game, int mx, int my, int dx)
{
	return (tile_at(game, mx, my) == '1'
		&& tile_at(game, mx + dx, my + 1) == '1'
		&& tile_at(game, mx + dx, my) != '1'
		&& tile_at(game, mx, my + 1) != '1');
}

/*
** How many walls the diagonal chain through the wall at (mx, my) has. It runs
** down to the right if dx is 1, and down to the left if dx is -1.
*/

static int	diagonal_length(t_game *game, int mx, int my, int dx)
{
	int	length;
	int	x;
	int	y;

	length = 1;
	x = mx;
	y = my;
	while (diagonal_step(game, x, y, dx) && ++length)
	{
		x += dx;
		y++;
	}
	x = mx;
	y = my;
	while (diagonal_step(game, x - dx, y - 1, dx) && ++length)
	{
		x -= dx;
		y--;
	}
	return (length);
}

/*
** Returns the sprite for a wall that is glass fence or faces the camera, or NULL
** for other walls and for walls whose sprite file is missing.
** Glass fence: more than 3 walls in a diagonal chain, touching only at corners.
** Facing the camera: floor, a collectible or the exit below it.
*/

mlx_texture_t	*facing_wall_texture(t_game *game, int mx, int my)
{
	char	below;

	if (game->glass_down_right_tex && diagonal_length(game, mx, my, 1) > 3)
		return (game->glass_down_right_tex);
	if (game->glass_down_left_tex && diagonal_length(game, mx, my, -1) > 3)
		return (game->glass_down_left_tex);
	below = tile_at(game, mx, my + 1);
	if (below == '0' || below == 'C' || below == 'E')
		return (game->facing_wall_tex);
	return (NULL);
}
