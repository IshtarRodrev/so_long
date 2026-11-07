/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_lamps.c                                   :+:      :+:    :+:   */
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

/* Queues (x, y) if it is a wall or a collectible and was not seen yet. */
static void	add_island_tile(t_flood *f, int x, int y)
{
	int	index;

	if (tile_at(f->game, x, y) != '1' && tile_at(f->game, x, y) != 'C')
		return ;
	index = tile_index(f->game, x, y);
	if (f->seen[index])
		return ;
	f->seen[index] = true;
	f->queue[f->qend] = index;
	f->qend++;
}

/* Marks the whole island of walls and collectibles around (x, y) as seen. */
static void	fill_island(t_flood *f, int x, int y)
{
	size_t	next;

	f->qend = 0;
	add_island_tile(f, x, y);
	next = 0;
	while (next < f->qend)
	{
		x = f->queue[next] % f->game->cols;
		y = f->queue[next] / f->game->cols;
		add_island_tile(f, x + 1, y);
		add_island_tile(f, x - 1, y);
		add_island_tile(f, x, y + 1);
		add_island_tile(f, x, y - 1);
		next++;
	}
}

/*
** One neon lamp per island of walls and collectibles (touching by a side):
** on the first wall of the island that touches at least 4 collectibles. The
** rest of that island is then marked as done. Returns NULL if memory runs out.
*/
bool	*lamp_tiles(t_game *game)
{
	t_flood	f;
	bool	*lamps;
	int		i;

	f.game = game;
	f.seen = ft_calloc((size_t) game->rows * game->cols, sizeof(bool));
	f.queue = malloc((size_t) game->rows * game->cols * sizeof(int));
	lamps = ft_calloc((size_t) game->rows * game->cols, sizeof(bool));
	i = -1;
	while (f.seen && f.queue && lamps && ++i < game->rows * game->cols)
	{
		if (!f.seen[i] && is_lamp_spot(game, i % game->cols, i / game->cols))
		{
			lamps[i] = true;
			fill_island(&f, i % game->cols, i / game->cols);
		}
	}
	if (!f.seen || !f.queue)
	{
		free(lamps);
		lamps = NULL;
	}
	free(f.seen);
	free(f.queue);
	return (lamps);
}

/* The neon lamp on a wall chosen by lamp_tiles, or NULL. */
mlx_texture_t	*lamp_texture(t_game *game, int mx, int my)
{
	if (game->layout.lamps[tile_index(game, mx, my)])
		return (game->textures.lamp);
	return (NULL);
}
