/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_glass_sprites.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Plain glass fence sprites and the variants where one side of the glass is
** dark (next to a closed area) or grass (next to the outside).
*/
void	load_glass_sprites(t_game *game)
{
	game->glass_down_right_tex = mlx_load_png(GLASS_DR_SPRITE_PATH);
	game->glass_down_left_tex = mlx_load_png(GLASS_DL_SPRITE_PATH);
	game->glass_dark_tex[GLASS_DR_LEFT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_right_dark_left.png");
	game->glass_dark_tex[GLASS_DR_RIGHT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_right_dark_right.png");
	game->glass_dark_tex[GLASS_DL_LEFT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_left_dark_left.png");
	game->glass_dark_tex[GLASS_DL_RIGHT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_left_dark_right.png");
	game->glass_grass_tex[GLASS_DR_LEFT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_right_grass_left.png");
	game->glass_grass_tex[GLASS_DR_RIGHT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_right_grass_right.png");
	game->glass_grass_tex[GLASS_DL_LEFT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_left_grass_left.png");
	game->glass_grass_tex[GLASS_DL_RIGHT] = mlx_load_png(SPRITE_DIR
			"/glass_fence/down_left_grass_right.png");
}

/* Deletes texture *tex if it was loaded and clears it. */
static void	delete_glass(mlx_texture_t **tex)
{
	if (*tex)
		mlx_delete_texture(*tex);
	*tex = NULL;
}

/* Deletes every glass fence sprite that was loaded. */
void	free_glass_sprites(t_game *game)
{
	int	i;

	delete_glass(&game->glass_down_right_tex);
	delete_glass(&game->glass_down_left_tex);
	i = 0;
	while (i < GLASS_SIDES)
	{
		delete_glass(&game->glass_dark_tex[i]);
		delete_glass(&game->glass_grass_tex[i]);
		i++;
	}
}
