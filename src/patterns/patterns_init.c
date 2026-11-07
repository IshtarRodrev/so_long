/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Works out how every tile of the map looks, once, before anything is drawn:
** which floor the player can reach, which unreachable floor is outside, and
** where flowerpots and trees go. Each step needs the one before it.
*/
void	init_patterns(t_game *game, const t_map *lay)
{
	game->reachable = reachable_tiles(lay);
	if (game->reachable)
		game->outside = outside_tiles(lay, game->reachable);
	if (game->outside)
		game->pots = pot_tiles(game);
	if (game->pots)
		game->trees = tree_tiles(game);
	if (!game->trees)
		fail(game, "memory allocation failed");
}
