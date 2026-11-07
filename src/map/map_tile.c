/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* True if (x, y) is a tile of the map. */
bool	in_map(t_game *game, int x, int y)
{
	return (x >= 0 && x < game->cols && y >= 0 && y < game->rows);
}

/* Index of tile (x, y) in the per-tile arrays (reachable, pots, ...). */
int	tile_index(t_game *game, int x, int y)
{
	return (y * game->cols + x);
}

/* The player's starting tile ('P') is floor. */

char	tile_at(t_game *game, int mx, int my)
{
	if (!in_map(game, mx, my))
		return ('\0');
	if (game->map[my][mx] == 'P')
		return ('0');
	return (game->map[my][mx]);
}
