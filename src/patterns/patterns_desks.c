/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_desks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:42:56 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** True if (x, y) is a seat in a sideways desk block: floor on one side, a wall
** on the other, and either another seat two tiles above or below it in the same
** column, or walls above and below it and a seat diagonally across its wall.
*/

bool	is_sideways_desk(t_game *game, int x, int y)
{
	char	left;
	char	right;
	char	top;
	char	bottom;
	int		wall_x;

	left = tile_at(game, x - 1, y);
	right = tile_at(game, x + 1, y);
	top = tile_at(game, x, y - 1);
	bottom = tile_at(game, x, y + 1);
	if (tile_at(game, x, y) != 'C' || !((left == '0' && right == '1')
			|| (left == '1' && right == '0')))
		return (false);
	wall_x = x - 1;
	if (right == '1')
		wall_x = x + 1;
	return ((top == '1' && bottom == '1'
			&& (tile_at(game, wall_x, y - 1) == 'C'
				|| tile_at(game, wall_x, y + 1) == 'C'))
		|| (top == '1' && tile_at(game, x, y - 2) == 'C')
		|| (bottom == '1' && tile_at(game, x, y + 2) == 'C'));
}

/*
** Returns the sprite for the wall at (x, y) if it is table in a sideways desk
** block, or NULL. It has seats above and below it, or at a corner one seat above
** or below it and one beside it, and floor on its open side.
*/

static mlx_texture_t	*sideways_table_texture(t_game *game, int x, int y)
{
	char	left;
	char	right;
	int		above;
	int		below;
	int		beside;

	left = tile_at(game, x - 1, y);
	right = tile_at(game, x + 1, y);
	above = is_sideways_desk(game, x, y - 1);
	below = is_sideways_desk(game, x, y + 1);
	beside = is_sideways_desk(game, x - 1, y)
		|| is_sideways_desk(game, x + 1, y);
	if (!((above && below) || ((above || below) && beside)))
		return (NULL);
	if (left == '0')
		return (game->textures.table[DIR_LEFT]);
	if (right == '0')
		return (game->textures.table[DIR_RIGHT]);
	return (NULL);
}

/*
** Returns the sprite for the wall at (x, y), or NULL if it is a plain wall.
** A wall is table if it sits between two collectibles, or if it is the corner
** of a desk block: a collectible on one side and one above or below it.
*/

mlx_texture_t	*empty_table_texture(t_game *game, int x, int y)
{
	mlx_texture_t	*sideways;
	int				sides;
	char			top;
	char			bottom;

	sideways = sideways_table_texture(game, x, y);
	if (sideways)
		return (sideways);
	sides = (tile_at(game, x - 1, y) == 'C')
		+ (tile_at(game, x + 1, y) == 'C');
	top = tile_at(game, x, y - 1);
	bottom = tile_at(game, x, y + 1);
	if (top == '0' && (sides == 2 || (sides == 1 && bottom == 'C')))
		return (game->textures.table[DIR_UP]);
	if (bottom == '0' && (sides == 2 || (sides == 1 && top == 'C')))
		return (game->textures.table[DIR_DOWN]);
	return (NULL);
}
