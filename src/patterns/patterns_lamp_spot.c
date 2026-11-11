/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_lamp_spot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* True if the collectible at (x, y) is drawn as a toilet. */
static bool	is_toilet(t_game *game, int x, int y)
{
	mlx_texture_t	*sprite;
	int				d;

	if (tile_at(game, x, y) != 'C')
		return (false);
	sprite = collectible_tile_texture(game, x, y);
	d = 0;
	while (d < DIR_COUNT)
	{
		if (sprite && sprite == game->textures.toilet[d])
			return (true);
		d++;
	}
	return (false);
}

/*
** Counts the collectibles touching (x, y), sides and corners. Returns -1 if
** one of them is a toilet: no lamp goes next to a toilet.
*/
static int	touching_collectibles(t_game *game, int x, int y)
{
	int	count;
	int	dx;
	int	dy;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (is_toilet(game, x + dx, y + dy))
				return (-1);
			if (tile_at(game, x + dx, y + dy) == 'C')
				count++;
			dx++;
		}
		dy++;
	}
	return (count);
}

/*
** True for a wall touching at least 4 collectibles (sides and corners), none
** of them a toilet. Needs the textures to be loaded (to recognise toilets).
*/
bool	is_lamp_spot(t_game *game, int x, int y)
{
	if (tile_at(game, x, y) != '1')
		return (false);
	return (touching_collectibles(game, x, y) >= 4);
}
