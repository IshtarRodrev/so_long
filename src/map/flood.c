/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/*
** Prepares a flood fill: passable says which tiles it may enter, spreads
** which tiles it may continue from (NULL: all). Returns false if memory runs
** out.
*/
bool	flood_init(t_flood *f, t_game *game, t_tile_test passable,
		t_tile_test spreads)
{
	f->game = game;
	f->passable = passable;
	f->spreads = spreads;
	f->qend = 0;
	f->seen = ft_calloc((size_t) game->rows * game->cols, sizeof(bool));
	f->queue = malloc((size_t) game->rows * game->cols * sizeof(int));
	if (f->seen && f->queue)
		return (true);
	free(f->seen);
	free(f->queue);
	f->seen = NULL;
	f->queue = NULL;
	return (false);
}

/* Queues (x, y) if it is in the map, passable and not seen yet. */
void	flood_add(t_flood *f, int x, int y)
{
	int	index;

	if (!in_map(f->game, x, y) || !f->passable(f->game, x, y))
		return ;
	index = tile_index(f->game, x, y);
	if (f->seen[index])
		return ;
	f->seen[index] = true;
	f->queue[f->qend] = index;
	f->qend++;
}

/*
** Fills from the tiles queued since queue[start]. Afterwards everything the
** fill reached from them is in queue[start .. qend) and marked in seen.
*/
void	flood_spread(t_flood *f, size_t start)
{
	size_t	next;
	int		x;
	int		y;

	next = start;
	while (next < f->qend)
	{
		x = f->queue[next] % f->game->cols;
		y = f->queue[next] / f->game->cols;
		next++;
		if (!f->spreads || f->spreads(f->game, x, y))
		{
			flood_add(f, x + 1, y);
			flood_add(f, x - 1, y);
			flood_add(f, x, y + 1);
			flood_add(f, x, y - 1);
		}
	}
}

/* Frees the queue and returns the seen tiles (the caller frees them). */
bool	*flood_finish(t_flood *f)
{
	free(f->queue);
	f->queue = NULL;
	return (f->seen);
}
