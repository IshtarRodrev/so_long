/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   game_render_tiles.c                               :+:      :+:    :+:    */
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

void	draw_exit_tile(t_game *game, int x, int y)
{
	mlx_texture_t	*layers[2];

	layers[0] = NULL;
	layers[1] = game->exit_tex;
	draw_texture_tile(game, layers, (t_point){x, y},
		((uint32_t) tile_color('0') << 8) | 0xFF);
}

void	draw_tile(t_game *game, int x, int y, int color)
{
	int			i;
	int			j;
	uint32_t	rgba;

	rgba = ((uint32_t) color << 8) | 0xFF;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(game->img, x * TILE_SIZE + j,
				SCORE_BAR_HEIGHT + y * TILE_SIZE + i, rgba);
			j++;
		}
		i++;
	}
}
