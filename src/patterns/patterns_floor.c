/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_ground.c                                  :+:      :+:    :+:   */
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
		if (my + k >= game->rows
			|| !game->outside[(my + k) * game->cols + mx])
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
mlx_image_t	*floor_tile(t_game *game, int mx, int my)
{
	int	index;

	index = my * game->cols + mx;
	if (game->outside[index])
	{
		if (game->asphalt_tex && near_wall_below(game, mx, my))
			return (image_for(game, game->asphalt_tex));
		if (game->grass_tex)
			return (image_for(game, game->grass_tex));
		return (game->color_img[IMG_OUTSIDE]);
	}
	if (!game->reachable[index])
		return (game->color_img[IMG_CLOSED]);
	return (game->color_img[IMG_FLOOR]);
}

/* The decoration drawn on top of a floor tile (flowerpot or tree), or NULL. */
mlx_image_t	*decoration_tile(t_game *game, int mx, int my)
{
	int	index;

	index = my * game->cols + mx;
	if (game->pots[index] && game->flowerpot_tex)
		return (image_for(game, game->flowerpot_tex));
	if (game->trees[index] && game->tree_tex)
		return (image_for(game, game->tree_tex));
	return (NULL);
}
