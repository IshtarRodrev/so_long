/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   game_render_texture.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: akechedz <akechedz@student.42heilbronn.de>#+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/06 17:48:30 by akechedz         #+#    #+#              */
/*   Updated: 2026/11/06 17:49:12 by akechedz        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static uint32_t	blend_pixel(uint8_t *p, uint32_t bg)
{
	uint8_t	a;
	uint8_t	out[3];
	int		i;

	a = p[3];
	if (a == 255)
		return (((uint32_t) p[0] << 24) | ((uint32_t) p[1] << 16)
			| ((uint32_t) p[2] << 8) | 0xFF);
	i = 0;
	while (i < 3)
	{
		out[i] = (uint8_t)(((int) p[i] * a
					+(int)((bg >> (24 - i * 8)) & 0xFF) * (255 - a)) / 255);
		i++;
	}
	return (((uint32_t) out[0] << 24) | ((uint32_t) out[1] << 16)
		| ((uint32_t) out[2] << 8) | 0xFF);
}

static uint32_t	texture_pixel(mlx_texture_t *tex, int i, int j, uint32_t bg)
{
	int	size;
	int	sx;
	int	sy;

	size = (int) tex->width;
	if ((int) tex->height > size)
		size = (int) tex->height;
	sx = j * size / TILE_SIZE - (size - (int) tex->width) / 2;
	sy = i * size / TILE_SIZE - (size - (int) tex->height) / 2;
	if (sx < 0 || sx >= (int) tex->width || sy < 0 || sy >= (int) tex->height)
		return (bg);
	return (blend_pixel(tex->pixels + ((size_t) sy * tex->width + sx) * 4, bg));
}

/*
** Draws layers[1] over bg at tile pos. If layers[0] is set, it is drawn between
** the two.
*/
void	draw_texture_tile(t_game *game, mlx_texture_t *layers[2],
	t_point pos, uint32_t bg)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			color = bg;
			if (layers[0])
				color = texture_pixel(layers[0], i, j, bg);
			mlx_put_pixel(game->img, pos.x * TILE_SIZE + j, SCORE_BAR_HEIGHT + pos.y * TILE_SIZE + i, texture_pixel(layers[1], i, j, color));
			j++;
		}
		i++;
	}
}

void	draw_player_tile(t_game *game, int x, int y)
{
	mlx_texture_t	*layers[2];
	int				frame_idx;
	char			tile;

	frame_idx = game->player_frame
		% game->player_frame_count[game->player_dir];
	layers[1] = game->player_tex[game->player_dir][frame_idx];
	layers[0] = NULL;
	tile = '0';
	if (is_collected(game, game->cam_x + x, game->cam_y + y))
	{
		layers[0] = collectible_tile_texture(game, game->cam_x + x,
				game->cam_y + y);
		if (!layers[0])
			tile = 'C';
	}
	draw_texture_tile(game, layers, (t_point){x, y},
		((uint32_t) tile_color(tile) << 8) | 0xFF);
}

void	load_exit_sprite(t_game *game)
{
	game->exit_tex = mlx_load_png(EXIT_SPRITE_PATH);
	if (!game->exit_tex)
	{
		ft_printf("Error: failed to load exit sprite\n");
		exit(1);
	}
}
