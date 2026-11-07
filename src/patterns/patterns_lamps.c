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

/* True for the tiles an island is made of: walls and collectibles. */
static bool	is_island_tile(t_game *game, int x, int y)
{
	return (tile_at(game, x, y) == '1' || tile_at(game, x, y) == 'C');
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
	size_t	start;
	int		i;

	lamps = ft_calloc((size_t) game->rows * game->cols, sizeof(bool));
	if (!lamps || !flood_init(&f, game, is_island_tile, NULL))
	{
		free(lamps);
		return (NULL);
	}
	i = -1;
	while (++i < game->rows * game->cols)
	{
		if (!f.seen[i] && is_lamp_spot(game, i % game->cols, i / game->cols))
		{
			lamps[i] = true;
			start = f.qend;
			flood_add(&f, i % game->cols, i / game->cols);
			flood_spread(&f, start);
		}
	}
	free(flood_finish(&f));
	return (lamps);
}

/* The neon lamp on a wall chosen by lamp_tiles, or NULL. */
mlx_texture_t	*lamp_texture(t_game *game, int mx, int my)
{
	if (game->layout.lamps[tile_index(game, mx, my)])
		return (game->textures.lamp);
	return (NULL);
}
