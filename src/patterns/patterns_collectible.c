/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_collectible.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 20:34:19 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/*
** A seat in a table line one tile thick: walls on
** two opposite sides and floor on
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
		return (game->desk_tex[DIR_LEFT]);
	if (left != '1' || right != '1' || top != '0' || bottom != '0')
		return (NULL);
	if (my < game->rows / 2)
		return (game->desk_tex[DIR_DOWN]);
	return (game->desk_tex[DIR_UP]);
}

/*
** A shower has walls above, below and on one side, and opens into a corridor.
** True if (mx, my) is a shower. Gives its sprite, which is NULL if the picture
** is missing.
*/

static bool	match_shower_texture(t_game *game, int mx, int my,
		mlx_texture_t **sprite)
{
	if (tile_at(game, mx, my - 1) != '1' || tile_at(game, mx, my + 1) != '1')
		return (false);
	if (tile_at(game, mx - 1, my) == '1' && is_corridor(game, mx + 1, my))
	{
		*sprite = game->shower_tex[DIR_RIGHT];
		return (true);
	}
	if (tile_at(game, mx + 1, my) == '1' && is_corridor(game, mx - 1, my))
	{
		*sprite = game->shower_tex[DIR_LEFT];
		return (true);
	}
	return (false);
}

/* Collectibles side by side against a wall are other equipment, not desks. */

static mlx_texture_t	*desk_texture(t_game *game, int mx, int my)
{
	bool	beside;
	char	top;
	char	bottom;

	beside = (tile_at(game, mx - 1, my) == 'C'
			|| tile_at(game, mx + 1, my) == 'C');
	top = tile_at(game, mx, my - 1);
	bottom = tile_at(game, mx, my + 1);
	if (is_sideways_desk(game, mx, my) && tile_at(game, mx - 1, my) == '0')
		return (game->desk_tex[DIR_LEFT]);
	if (is_sideways_desk(game, mx, my))
		return (game->desk_tex[DIR_RIGHT]);
	if (top == '0' && (bottom == 'C' || (bottom == '1' && !beside)))
		return (game->desk_tex[DIR_UP]);
	if (bottom == '0' && (top == 'C' || (top == '1' && !beside)))
		return (game->desk_tex[DIR_DOWN]);
	return (thin_line_desk_texture(game, mx, my));
}

/*
** Returns the sprite for the collectible at (mx, my), or NULL if no rule fits.
** Toilets, sinks, kitchens and vending machines are recognised by their row or
** column.
*/

mlx_texture_t	*collectible_tile_texture(t_game *game, int mx, int my)
{
	mlx_texture_t	*sprite;

	sprite = row_texture(game, mx, my);
	if (sprite)
		return (sprite);
	if (match_column_texture(game, mx, my, &sprite))
		return (sprite);
	if (match_shower_texture(game, mx, my, &sprite))
		return (sprite);
	return (desk_texture(game, mx, my));
}
