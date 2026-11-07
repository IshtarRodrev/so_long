/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_outside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* True for a tile the player cannot reach that is not a wall. */
static bool	is_unreachable_floor(t_game *game, int x, int y)
{
	return (tile_at(game, x, y) != '1'
		&& !game->layout.reachable[tile_index(game, x, y)]);
}

/*
** Flood fill from every border tile through floor the player cannot reach:
** true for every tile outside the walls. Returns NULL if memory runs out.
*/
bool	*outside_tiles(t_game *game)
{
	t_flood	f;
	int		i;

	if (!flood_init(&f, game, is_unreachable_floor, NULL))
		return (NULL);
	i = -1;
	while (++i < game->cols)
	{
		flood_add(&f, i, 0);
		flood_add(&f, i, game->rows - 1);
	}
	i = -1;
	while (++i < game->rows)
	{
		flood_add(&f, 0, i);
		flood_add(&f, game->cols - 1, i);
	}
	flood_spread(&f, 0);
	return (flood_finish(&f));
}
