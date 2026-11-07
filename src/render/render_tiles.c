/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_tiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:48:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:12 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"

/* Shows img centred on map tile (mx, my). Returns the instance index. */
static int	put_tile(t_game *game, mlx_image_t *img, int mx, int my)
{
	int	x;
	int	y;

	x = (mx - game->cam_x) * TILE_SIZE + (TILE_SIZE - (int) img->width) / 2;
	y = SCORE_BAR_HEIGHT + (my - game->cam_y) * TILE_SIZE
		+ (TILE_SIZE - (int) img->height) / 2;
	return (put_image(game, img, x, y));
}

/*
** A task to do shows its sprite (if its shape has one) on the floor, under the
** broken sign. The sign is the cover: hiding it marks the task as done.
*/
static void	place_collectible(t_game *game, int mx, int my)
{
	mlx_texture_t	*sprite;

	put_tile(game, game->color_img[IMG_FLOOR], mx, my);
	sprite = collectible_tile_texture(game, mx, my);
	if (sprite)
		put_tile(game, image_for(game, sprite), mx, my);
	game->cover[my * game->cols + mx] = put_tile(game,
			image_for(game, game->broken_sign_tex), mx, my);
}

static void	place_wall(t_game *game, int mx, int my)
{
	mlx_texture_t	*sprite;

	sprite = empty_table_texture(game, mx, my);
	if (!sprite)
		sprite = facing_wall_texture(game, mx, my);
	if (!sprite)
	{
		put_tile(game, game->color_img[IMG_WALL], mx, my);
		return ;
	}
	put_tile(game, game->color_img[IMG_FLOOR], mx, my);
	put_tile(game, image_for(game, sprite), mx, my);
}

/* Puts the images of map tile (mx, my) in the window. */
void	place_tile(t_game *game, int mx, int my)
{
	char	tile;

	tile = game->map[my][mx];
	if (tile == 'C')
	{
		place_collectible(game, mx, my);
		if (is_collected(game, mx, my))
			uncover_tile(game, mx, my);
	}
	else if (tile == '1')
		place_wall(game, mx, my);
	else
	{
		put_tile(game, game->color_img[IMG_FLOOR], mx, my);
		if (tile == 'E')
			put_tile(game, image_for(game, game->exit_tex), mx, my);
	}
}

/* Hides the cover of the collected task at (mx, my). */
void	uncover_tile(t_game *game, int mx, int my)
{
	mlx_image_t	*sign;

	sign = image_for(game, game->broken_sign_tex);
	sign->instances[game->cover[my * game->cols + mx]].enabled = false;
}
