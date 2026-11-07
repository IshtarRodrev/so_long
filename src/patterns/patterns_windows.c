/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_windows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** True for an outer wall seen from inside: the outside is right above it and
** floor, a collectible or the exit is right below it.
*/
static bool	is_outer_wall(t_game *game, int mx, int my)
{
	char	below;

	if (tile_at(game, mx, my) != '1' || tile_at(game, mx, my - 1) != '0'
		|| !game->layout.outside[tile_index(game, mx, my - 1)])
		return (false);
	below = tile_at(game, mx, my + 1);
	return (below == '0' || below == 'C' || below == 'E');
}

/*
** In each horizontal run of outer walls, every 2nd and 3rd tile is a window:
** wall, window, window, wall, window, window, ... counted from the left end
** of the run. Runs shorter than WINDOW_MIN_RUN get no windows. Returns the
** window sprite, or NULL.
*/
mlx_texture_t	*window_texture(t_game *game, int mx, int my)
{
	int	left;
	int	right;

	if (!game->textures.window || !is_outer_wall(game, mx, my))
		return (NULL);
	left = 0;
	while (is_outer_wall(game, mx - left - 1, my))
		left++;
	right = 0;
	while (is_outer_wall(game, mx + right + 1, my))
		right++;
	if (left + right + 1 < WINDOW_MIN_RUN || left % 3 == 0)
		return (NULL);
	return (game->textures.window);
}
