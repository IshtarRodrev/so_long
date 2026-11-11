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

#include "so_long.h"

/*
** A seat in a table line one tile thick: walls on
** two opposite sides and floor on
** the other two. Vertical lines always face left, horizontal lines face the
** centre of the map.
*/

static mlx_texture_t	*thin_line_desk_texture(t_game *game, int x, int y)
{
	char	left;
	char	right;
	char	top;
	char	bottom;

	left = tile_at(game, x - 1, y);
	right = tile_at(game, x + 1, y);
	top = tile_at(game, x, y - 1);
	bottom = tile_at(game, x, y + 1);
	if (top == '1' && bottom == '1' && left == '0' && right == '0')
		return (game->textures.desk[DIR_LEFT]);
	if (left != '1' || right != '1' || top != '0' || bottom != '0')
		return (NULL);
	if (y < game->rows / 2)
		return (game->textures.desk[DIR_DOWN]);
	return (game->textures.desk[DIR_UP]);
}

/*
** A shower has walls above, below and on one side, and opens into a corridor.
** True if (x, y) is a shower. Gives its sprite, which is NULL if the picture
** is missing.
*/

static bool	match_shower_texture(t_game *game, int x, int y,
		mlx_texture_t **sprite)
{
	if (tile_at(game, x, y - 1) != '1' || tile_at(game, x, y + 1) != '1')
		return (false);
	if (tile_at(game, x - 1, y) == '1' && is_corridor(game, x + 1, y))
	{
		*sprite = game->textures.shower[DIR_RIGHT];
		return (true);
	}
	if (tile_at(game, x + 1, y) == '1' && is_corridor(game, x - 1, y))
	{
		*sprite = game->textures.shower[DIR_LEFT];
		return (true);
	}
	return (false);
}

/* Collectibles side by side against a wall are other equipment, not desks. */

static mlx_texture_t	*desk_texture(t_game *game, int x, int y)
{
	bool	beside;
	char	top;
	char	bottom;

	beside = (tile_at(game, x - 1, y) == 'C'
			|| tile_at(game, x + 1, y) == 'C');
	top = tile_at(game, x, y - 1);
	bottom = tile_at(game, x, y + 1);
	if (is_sideways_desk(game, x, y) && tile_at(game, x - 1, y) == '0')
		return (game->textures.desk[DIR_LEFT]);
	if (is_sideways_desk(game, x, y))
		return (game->textures.desk[DIR_RIGHT]);
	if (top == '0' && (bottom == 'C' || (bottom == '1' && !beside)))
		return (game->textures.desk[DIR_UP]);
	if (bottom == '0' && (top == 'C' || (top == '1' && !beside)))
		return (game->textures.desk[DIR_DOWN]);
	return (thin_line_desk_texture(game, x, y));
}

/*
** Returns the sprite for the collectible at (x, y), or NULL if no rule fits.
** Toilets, sinks, kitchens and vending machines are recognised by their row or
** column.
*/

mlx_texture_t	*collectible_tile_texture(t_game *game, int x, int y)
{
	mlx_texture_t	*sprite;

	sprite = row_texture(game, x, y);
	if (sprite)
		return (sprite);
	if (match_column_texture(game, x, y, &sprite))
		return (sprite);
	if (match_shower_texture(game, x, y, &sprite))
		return (sprite);
	return (desk_texture(game, x, y));
}
