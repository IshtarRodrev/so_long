/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:48:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:12 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Shows img centred on map tile (x, y). Returns the instance index. */
static int	put_tile(t_game *game, mlx_image_t *img, int x, int y)
{
	int	px;
	int	py;

	px = (x - game->cam.x) * TILE_SIZE + (TILE_SIZE - (int) img->width) / 2;
	py = SCORE_BAR_HEIGHT + (y - game->cam.y) * TILE_SIZE
		+ (TILE_SIZE - (int) img->height) / 2;
	return (put_image(game, img, px, py));
}

/*
** A task to do shows its sprite (if its shape has one) on the floor, under the
** broken sign. Its instance index is kept in sign_instance: hiding it marks
** the collectible as collected.
*/
static void	place_collectible(t_game *game, int x, int y)
{
	mlx_texture_t	*sprite;

	put_tile(game, game->scene.color[IMG_FLOOR], x, y);
	sprite = collectible_tile_texture(game, x, y);
	if (sprite)
		put_tile(game, cached_image(game, sprite), x, y);
	game->scene.sign_instance[tile_index(game, x, y)] = put_tile(game,
			cached_image(game, game->textures.broken_sign), x, y);
}

static void	place_wall(t_game *game, int x, int y)
{
	mlx_texture_t	*sprite;

	sprite = window_texture(game, x, y);
	if (sprite)
	{
		put_tile(game, floor_image(game, x, y - 1), x, y);
		put_tile(game, cached_image(game, sprite), x, y);
		return ;
	}
	sprite = lamp_texture(game, x, y);
	if (!sprite)
		sprite = empty_table_texture(game, x, y);
	if (!sprite)
		sprite = facing_wall_texture(game, x, y);
	if (!sprite)
	{
		put_tile(game, game->scene.color[IMG_WALL], x, y);
		return ;
	}
	put_tile(game, game->scene.color[IMG_FLOOR], x, y);
	put_tile(game, cached_image(game, sprite), x, y);
}

/* Puts the images of map tile (x, y) in the window. */
void	place_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == 'C')
	{
		place_collectible(game, x, y);
		if (is_collected(game, x, y))
			uncover_tile(game, x, y);
	}
	else if (tile == '1')
		place_wall(game, x, y);
	else
	{
		put_tile(game, floor_image(game, x, y), x, y);
		if (decoration_image(game, x, y))
			put_tile(game, decoration_image(game, x, y), x, y);
		if (tile == 'E')
			put_tile(game, cached_image(game, game->textures.exit), x, y);
	}
}

/* Hides the broken sign of the collected collectible at (x, y). */
void	uncover_tile(t_game *game, int x, int y)
{
	mlx_image_t	*sign;
	int			instance;

	sign = cached_image(game, game->textures.broken_sign);
	instance = game->scene.sign_instance[tile_index(game, x, y)];
	sign->instances[instance].enabled = false;
}
