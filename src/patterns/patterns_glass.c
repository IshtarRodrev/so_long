/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_glass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* SIDE_DARK for closed-area floor, SIDE_GRASS for outside floor, else 0. */
static int	side_kind(t_game *game, int x, int y)
{
	int	index;

	if (y < 0 || y >= game->rows || x < 0 || x >= game->cols
		|| game->map[y][x] != '0')
		return (0);
	index = y * game->cols + x;
	if (game->outside[index])
		return (SIDE_GRASS);
	if (!game->reachable[index])
		return (SIDE_DARK);
	return (0);
}

/*
** The glass sprite for the fence wall at (mx, my). dx is 1 for a fence going
** down to the right, -1 for one going down to the left. Its left side touches
** (mx - 1, my) and (mx, my + dx), its right side (mx + 1, my) and
** (mx, my - dx). A side next to a closed area is drawn dark, a side next to
** the outside is drawn as grass, otherwise the plain sprite is used.
*/
mlx_texture_t	*glass_texture(t_game *game, int mx, int my, int dx)
{
	int	left;
	int	l_kind;
	int	r_kind;

	left = GLASS_DR_LEFT;
	if (dx < 0)
		left = GLASS_DL_LEFT;
	l_kind = side_kind(game, mx - 1, my) | side_kind(game, mx, my + dx);
	r_kind = side_kind(game, mx + 1, my) | side_kind(game, mx, my - dx);
	if ((l_kind & SIDE_DARK) && game->glass_dark_tex[left])
		return (game->glass_dark_tex[left]);
	if ((r_kind & SIDE_DARK) && game->glass_dark_tex[left + 1])
		return (game->glass_dark_tex[left + 1]);
	if ((l_kind & SIDE_GRASS) && game->glass_grass_tex[left])
		return (game->glass_grass_tex[left]);
	if ((r_kind & SIDE_GRASS) && game->glass_grass_tex[left + 1])
		return (game->glass_grass_tex[left + 1]);
	if (dx < 0)
		return (game->glass_down_left_tex);
	return (game->glass_down_right_tex);
}
