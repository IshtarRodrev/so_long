/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_pots.c                                    :+:      :+:    :+:   */
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

/* True for floor in a closed area the player can never reach (dark). */
static bool	is_closed_floor(t_game *game, int x, int y)
{
	int	index;

	if (tile_at(game, x, y) != '0')
		return (false);
	index = tile_index(game, x, y);
	return (!game->layout.reachable[index] && !game->layout.outside[index]);
}

/*
** Rightmost column, top and bottom row of the area in queue[start .. qend),
** and how many of its tiles are in that rightmost column (its height).
*/
static t_area	area_bounds(t_flood *f, size_t start)
{
	t_area	a;
	size_t	i;
	int		x;
	int		y;

	a = (t_area){-1, f->game->rows, -1, 0};
	i = start;
	while (i < f->qend)
	{
		x = f->queue[i] % f->game->cols;
		y = f->queue[i] / f->game->cols;
		if (x > a.right)
		{
			a.right = x;
			a.height = 0;
		}
		if (x == a.right)
			a.height++;
		if (y < a.top)
			a.top = y;
		if (y > a.bottom)
			a.bottom = y;
		i++;
	}
	return (a);
}

/*
** Marks in pots the area in queue[start .. qend): its rightmost column,
** its top row and its bottom row - only if that rightmost column is a real
** vertical row (2 tiles or more). An area ending in a diagonal gets none.
*/
static void	mark_area(t_flood *f, size_t start, bool *pots)
{
	t_area	a;
	size_t	i;
	int		x;
	int		y;

	a = area_bounds(f, start);
	if (a.height < 2)
		return ;
	i = start;
	while (i < f->qend)
	{
		x = f->queue[i] % f->game->cols;
		y = f->queue[i] / f->game->cols;
		if (x == a.right || y == a.top || y == a.bottom)
			pots[f->queue[i]] = true;
		i++;
	}
}

/*
** True for every tile that shows a flowerpot. Needs game->layout.reachable and
** game->layout.outside. Returns NULL if memory runs out.
*/
bool	*pot_tiles(t_game *game)
{
	t_flood	f;
	bool	*pots;
	size_t	start;
	int		i;

	pots = ft_calloc((size_t) game->rows * game->cols, sizeof(bool));
	if (!pots || !flood_init(&f, game, is_closed_floor, NULL))
	{
		free(pots);
		return (NULL);
	}
	i = -1;
	while (++i < game->rows * game->cols)
	{
		start = f.qend;
		flood_add(&f, i % game->cols, i / game->cols);
		flood_spread(&f, start);
		mark_area(&f, start, pots);
	}
	free(flood_finish(&f));
	return (pots);
}
