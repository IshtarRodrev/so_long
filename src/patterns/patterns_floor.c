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

#include "so_long.h"

/*
** True if a wall lies at most ASPHALT_ROWS tiles below (mx, my), with only
** outside floor in between.
*/
static bool	near_wall_below(t_game *game, int mx, int my)
{
	int	k;

	k = 1;
	while (k <= ASPHALT_ROWS)
	{
		if (tile_at(game, mx, my + k) == '1')
			return (true);
		if (!in_map(game, mx, my + k)
			|| !game->layout.outside[tile_index(game, mx, my + k)])
			return (false);
		k++;
	}
	return (false);
}

/*
** The image a floor tile is drawn with. Outside the walls: asphalt on the
** ASPHALT_ROWS rows above a wall, grass elsewhere (brown if a sprite is
** missing). Floor the player can never reach inside: near-black. Floor the
** player can walk on: grey.
*/
mlx_image_t	*floor_image(t_game *game, int mx, int my)
{
	int	index;

	index = tile_index(game, mx, my);
	if (game->layout.outside[index])
	{
		if (game->textures.asphalt && near_wall_below(game, mx, my))
			return (cached_image(game, game->textures.asphalt));
		if (game->textures.grass)
			return (cached_image(game, game->textures.grass));
		return (game->scene.color[IMG_OUTSIDE]);
	}
	if (!game->layout.reachable[index])
		return (game->scene.color[IMG_CLOSED]);
	return (game->scene.color[IMG_FLOOR]);
}

/* The decoration drawn on top of a floor tile (flowerpot or tree), or NULL. */
mlx_image_t	*decoration_image(t_game *game, int mx, int my)
{
	int	index;

	index = tile_index(game, mx, my);
	if (game->layout.pots[index] && game->textures.flowerpot)
		return (cached_image(game, game->textures.flowerpot));
	if (game->layout.trees[index] && game->textures.tree)
		return (cached_image(game, game->textures.tree));
	return (NULL);
}
