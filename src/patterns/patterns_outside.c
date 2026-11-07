/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_floor.c                                   :+:      :+:    :+:   */
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

/* Marks (x, y) as outside and queues it if it is unreachable floor. */
static void	add_tile(t_fill *f, int x, int y)
{
	int	index;

	if (y < 0 || y >= (int) f->map->rows || x < 0 || x >= (int) f->map->cols)
		return ;
	index = y * (int) f->map->cols + x;
	if (f->map->lines[y][x] == '1' || f->reachable[index] || f->outside[index])
		return ;
	f->outside[index] = true;
	f->queue[f->qend++] = index;
}

/* Starts the fill from every tile on the border of the map. */
static void	add_border(t_fill *f)
{
	int	i;

	i = -1;
	while (++i < (int) f->map->cols)
	{
		add_tile(f, i, 0);
		add_tile(f, i, (int) f->map->rows - 1);
	}
	i = -1;
	while (++i < (int) f->map->rows)
	{
		add_tile(f, 0, i);
		add_tile(f, (int) f->map->cols - 1, i);
	}
}

/* Spreads from every queued tile to its unreachable floor neighbours. */
static void	spread(t_fill *f)
{
	size_t	next;
	int		x;
	int		y;

	next = 0;
	while (next < f->qend)
	{
		x = f->queue[next] % (int) f->map->cols;
		y = f->queue[next] / (int) f->map->cols;
		next++;
		add_tile(f, x + 1, y);
		add_tile(f, x - 1, y);
		add_tile(f, x, y + 1);
		add_tile(f, x, y - 1);
	}
}

/*
** Flood fill from the map border through floor the player cannot reach:
** true for every tile outside the walls. Returns NULL if memory runs out.
*/
bool	*outside_tiles(const t_map *map, const bool *reachable)
{
	t_fill	f;

	ft_bzero(&f, sizeof(f));
	f.map = map;
	f.reachable = reachable;
	f.outside = ft_calloc(map->rows * map->cols, sizeof(bool));
	f.queue = malloc(map->rows * map->cols * sizeof(int));
	if (!f.outside || !f.queue)
	{
		free(f.outside);
		free(f.queue);
		return (NULL);
	}
	add_border(&f);
	spread(&f);
	free(f.queue);
	return (f.outside);
}
