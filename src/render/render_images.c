/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:48:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 20:46:20 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"

/* Makes an image of tex, scaled to fit a tile and keeping its proportions. */
mlx_image_t	*texture_image(t_game *game, mlx_texture_t *tex)
{
	mlx_image_t	*img;
	uint32_t	size;
	uint32_t	w;
	uint32_t	h;

	size = tex->width;
	if (tex->height > size)
		size = tex->height;
	w = tex->width * TILE_SIZE / size;
	h = tex->height * TILE_SIZE / size;
	if (w == 0)
		w = 1;
	if (h == 0)
		h = 1;
	img = mlx_texture_to_image(game->mlx, tex);
	if (!img || !mlx_resize_image(img, w, h))
	{
		print_error("failed to create image", NULL);
		exit_game(game, 1);
	}
	return (img);
}

/* The one map image made from tex: made on first use, then reused. */
mlx_image_t	*image_for(t_game *game, mlx_texture_t *tex)
{
	int	i;

	i = 0;
	while (i < game->cache_count)
	{
		if (game->cache_tex[i] == tex)
			return (game->cache_img[i]);
		i++;
	}
	if (game->cache_count == IMG_CACHE)
	{
		print_error("too many different sprites", NULL);
		exit_game(game, 1);
	}
	game->cache_tex[i] = tex;
	game->cache_img[i] = texture_image(game, tex);
	game->cache_count++;
	return (game->cache_img[i]);
}

/* A w x h image of one colour: a single pixel stretched by MLX. */
mlx_image_t	*color_image(t_game *game, uint32_t rgba, uint32_t w, uint32_t h)
{
	mlx_image_t	*img;

	img = mlx_new_image(game->mlx, 1, 1);
	if (!img)
	{
		print_error("failed to create image", NULL);
		exit_game(game, 1);
	}
	mlx_put_pixel(img, 0, 0, rgba);
	if (!mlx_resize_image(img, w, h))
	{
		print_error("failed to create image", NULL);
		exit_game(game, 1);
	}
	return (img);
}

/* Shows a new instance of img at window position (x, y). Returns its index. */
int	put_image(t_game *game, mlx_image_t *img, int x, int y)
{
	int	index;

	index = mlx_image_to_window(game->mlx, img, x, y);
	if (index < 0)
	{
		print_error("failed to put image to window", NULL);
		exit_game(game, 1);
	}
	return (index);
}

void	load_exit_sprite(t_game *game)
{
	game->exit_tex = mlx_load_png(EXIT_SPRITE_PATH);
	if (!game->exit_tex)
	{
		print_error("failed to load exit sprite", NULL);
		exit_game(game, 1);
	}
}
