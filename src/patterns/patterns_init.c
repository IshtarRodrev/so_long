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
** where flowerpots, trees and lamps go. Each step needs the one before it.
** Runs after load_textures: lamps check which collectibles are toilets.
*/
void	init_patterns(t_game *game, const t_map *parsed)
{
	game->layout.reachable = reachable_tiles(game, parsed->player);
	if (game->layout.reachable)
		game->layout.outside = outside_tiles(game);
	if (game->layout.outside)
		game->layout.pots = pot_tiles(game);
	if (game->layout.pots)
		game->layout.trees = tree_tiles(game);
	if (game->layout.trees)
		game->layout.lamps = lamp_tiles(game);
	if (!game->layout.lamps)
		fail(game, "memory allocation failed");
}
