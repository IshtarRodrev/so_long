/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_desks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:42:56 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/*
** True if (mx, my) is a seat in a sideways desk block: floor on one side, a wall
** on the other, and either another seat two tiles above or below it in the same
** column, or walls above and below it and a seat diagonally across its wall.
*/

static bool	is_sideways_desk(t_game *game, int mx, int my)
{
	char	left;
	char	right;
	char	top;
	char	bottom;
	int		wall_x;

	left = tile_at(game, mx - 1, my);
	right = tile_at(game, mx + 1, my);
	top = tile_at(game, mx, my - 1);
	bottom = tile_at(game, mx, my + 1);
	if (tile_at(game, mx, my) != 'C' || !((left == '0' && right == '1')
			|| (left == '1' && right == '0')))
		return (false);
	wall_x = mx - 1;
	if (right == '1')
		wall_x = mx + 1;
	return ((top == '1' && bottom == '1'
			&& (tile_at(game, wall_x, my - 1) == 'C'
				|| tile_at(game, wall_x, my + 1) == 'C'))
		|| (top == '1' && tile_at(game, mx, my - 2) == 'C')
		|| (bottom == '1' && tile_at(game, mx, my + 2) == 'C'));
}

/*
** Returns the sprite for the wall at (mx, my) if it is table in a sideways desk
** block, or NULL. It has seats above and below it, or at a corner one seat above
** or below it and one beside it, and floor on its open side.
*/

static mlx_texture_t	*sideways_table_texture(t_game *game, int mx, int my)
{
	char	left;
	char	right;
	int		above;
	int		below;
	int		beside;

	left = tile_at(game, mx - 1, my);
	right = tile_at(game, mx + 1, my);
	above = is_sideways_desk(game, mx, my - 1);
	below = is_sideways_desk(game, mx, my + 1);
	beside = is_sideways_desk(game, mx - 1, my)
		|| is_sideways_desk(game, mx + 1, my);
	if (!((above && below) || ((above || below) && beside)))
		return (NULL);
	if (left == '0')
		return (game->table_tex[FACE_LEFT]);
	if (right == '0')
		return (game->table_tex[FACE_RIGHT]);
	return (NULL);
}

/*
** A seat in a table line one tile thick: walls on two opposite sides and floor on
** the other two. Vertical lines always face left, horizontal lines face the
** centre of the map.
*/

static mlx_texture_t	*thin_line_desk_texture(t_game *game, int mx, int my)
{
	char	left;
	char	right;
	char	top;
	char	bottom;

	left = tile_at(game, mx - 1, my);
	right = tile_at(game, mx + 1, my);
	top = tile_at(game, mx, my - 1);
	bottom = tile_at(game, mx, my + 1);
	if (top == '1' && bottom == '1' && left == '0' && right == '0')
		return (game->desk_tex[FACE_LEFT]);
	if (left != '1' || right != '1' || top != '0' || bottom != '0')
		return (NULL);
	if (my < game->rows / 2)
		return (game->desk_tex[FACE_DOWN]);
	return (game->desk_tex[FACE_UP]);
}

/*
** Returns the sprite for the collectible at (mx, my), or NULL if no rule fits.
** Toilets, sinks, kitchens and vending machines are recognised by their row or
** column.
** A shower has walls above, below and on one side, and opens into a corridor.
** Collectibles side by side against a wall are other equipment, not desks.
*/

mlx_texture_t	*collectible_tile_texture(t_game *game, int mx, int my)
{
	mlx_texture_t	*row;
	bool			beside;
	char			top;
	char			bottom;

	row = row_texture(game, mx, my);
	if (row)
		return (row);
	if (column_sprite(game, mx, my, &row))
		return (row);
	beside = (tile_at(game, mx - 1, my) == 'C'
			|| tile_at(game, mx + 1, my) == 'C');
	top = tile_at(game, mx, my - 1);
	bottom = tile_at(game, mx, my + 1);
	if (top == '1' && bottom == '1' && tile_at(game, mx - 1, my) == '1'
		&& is_corridor(game, mx + 1, my))
		return (game->shower_tex[FACE_RIGHT]);
	if (top == '1' && bottom == '1' && tile_at(game, mx + 1, my) == '1'
		&& is_corridor(game, mx - 1, my))
		return (game->shower_tex[FACE_LEFT]);
	if (is_sideways_desk(game, mx, my) && tile_at(game, mx - 1, my) == '0')
		return (game->desk_tex[FACE_LEFT]);
	if (is_sideways_desk(game, mx, my))
		return (game->desk_tex[FACE_RIGHT]);
	if (top == '0' && (bottom == 'C' || (bottom == '1' && !beside)))
		return (game->desk_tex[FACE_UP]);
	if (bottom == '0' && (top == 'C' || (top == '1' && !beside)))
		return (game->desk_tex[FACE_DOWN]);
	return (thin_line_desk_texture(game, mx, my));
}

/*
** Returns the sprite for the wall at (mx, my), or NULL if it is a plain wall.
** A wall is table if it sits between two collectibles, or if it is the corner
** of a desk block: a collectible on one side and one above or below it.
*/

mlx_texture_t	*empty_table_texture(t_game *game, int mx, int my)
{
	mlx_texture_t	*sideways;
	int				sides;
	char			top;
	char			bottom;

	sideways = sideways_table_texture(game, mx, my);
	if (sideways)
		return (sideways);
	sides = (tile_at(game, mx - 1, my) == 'C')
		+ (tile_at(game, mx + 1, my) == 'C');
	top = tile_at(game, mx, my - 1);
	bottom = tile_at(game, mx, my + 1);
	if (top == '0' && (sides == 2 || (sides == 1 && bottom == 'C')))
		return (game->table_tex[FACE_UP]);
	if (bottom == '0' && (sides == 2 || (sides == 1 && top == 'C')))
		return (game->table_tex[FACE_DOWN]);
	return (NULL);
}
