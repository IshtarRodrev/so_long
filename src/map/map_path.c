/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:22 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:19 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_walkable(t_game *game, int x, int y)
{
	return (tile_at(game, x, y) != '1');
}

/* The exit ends a path: it stays locked until every collectible is taken. */
static bool	is_not_exit(t_game *game, int x, int y)
{
	return (tile_at(game, x, y) != 'E');
}

/*
** Flood fill from start through everything that is not a wall, not going on
** past the exit: true for every tile the player can reach. NULL if memory
** runs out.
*/
bool	*reachable_tiles(t_game *game, t_point start)
{
	t_flood	f;

	if (!flood_init(&f, game, is_walkable, is_not_exit))
		return (NULL);
	flood_add(&f, start.x, start.y);
	flood_spread(&f, 0);
	return (flood_finish(&f));
}
