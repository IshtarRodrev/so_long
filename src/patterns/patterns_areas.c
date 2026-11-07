/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_areas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* True for floor in a closed area the player can never reach (dark). */
static bool	is_closed_floor(t_game *game, int x, int y)
{
	int	index;

	if (!in_map(game, x, y) || game->map[y][x] != '0')
		return (false);
	index = tile_index(game, x, y);
	return (!game->reachable[index] && !game->outside[index]);
}

/* Queues (x, y) if it is closed-area floor and was not seen yet. */
void	add_area_tile(t_pot_fill *f, int x, int y)
{
	int	index;

	if (!is_closed_floor(f->game, x, y))
		return ;
	index = tile_index(f->game, x, y);
	if (f->seen[index])
		return ;
	f->seen[index] = true;
	f->queue[f->qend] = index;
	f->qend++;
}

/*
** Flood fills one closed area. Its first tile is queue[start]; afterwards the
** whole area is in queue[start .. qend).
*/
void	fill_area(t_pot_fill *f, size_t start)
{
	size_t	next;
	int		x;
	int		y;

	next = start;
	while (next < f->qend)
	{
		x = f->queue[next] % f->game->cols;
		y = f->queue[next] / f->game->cols;
		add_area_tile(f, x + 1, y);
		add_area_tile(f, x - 1, y);
		add_area_tile(f, x, y + 1);
		add_area_tile(f, x, y - 1);
		next++;
	}
}
