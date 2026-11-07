/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:22 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:19 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

/* True if tile number i lies on the border of the map. */
static bool	is_edge(t_game *game, int i)
{
	return (i % game->cols == 0 || i % game->cols == game->cols - 1
		|| i / game->cols == 0 || i / game->cols == game->rows - 1);
}

/*
** Checks what the player can reach (seen) and prints why the map fails, if
** it does. Returns 1 if the path is valid.
*/
static int	report_path(t_game *game, const t_map *parsed, const bool *seen)
{
	int		i;
	int		collectibles;
	bool	exit;
	bool	leaked;

	collectibles = 0;
	exit = false;
	leaked = false;
	i = -1;
	while (++i < game->rows * game->cols)
	{
		if (!seen[i])
			continue ;
		collectibles += (game->map[i / game->cols][i % game->cols] == 'C');
		exit = exit || game->map[i / game->cols][i % game->cols] == 'E';
		leaked = leaked || is_edge(game, i);
	}
	if (leaked)
		return (map_error("map is not sealed, player can reach the edge"));
	if (collectibles != parsed->collectibles)
		return (map_error("not all collectibles are reachable"));
	if (!exit)
		return (map_error("exit is not reachable"));
	return (1);
}

/* Flood fill from P: every C and the exit must be reachable. */
int	path_is_valid(t_game *game, const t_map *parsed)
{
	bool	*seen;
	int		valid;

	seen = reachable_tiles(game, parsed->player);
	if (!seen)
		return (map_error("memory allocation failed"));
	valid = report_path(game, parsed, seen);
	free(seen);
	return (valid);
}
