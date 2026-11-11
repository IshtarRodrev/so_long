/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/*
** What the scene needs before tiles are placed: the plain colour tiles and,
** per tile, room for the index of its broken-sign instance (sign_instance).
*/
void	init_render(t_game *game)
{
	static const uint32_t	rgba[IMG_COLORS] = {RGBA_FLOOR, RGBA_WALL,
		RGBA_CLOSED, RGBA_OUTSIDE};
	int						i;

	game->scene.sign_instance = ft_calloc((size_t) game->rows * game->cols,
			sizeof(int));
	if (!game->scene.sign_instance)
		fail(game, "memory allocation failed");
	i = 0;
	while (i < IMG_COLORS)
	{
		game->scene.color[i] = color_image(game, rgba[i], TILE_SIZE, TILE_SIZE);
		i++;
	}
}
