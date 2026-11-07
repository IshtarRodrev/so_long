/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:28 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:21 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	clear_menu_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < MENU_IMAGES)
	{
		if (game->scene.menu[i])
			mlx_delete_image(game->mlx, game->scene.menu[i]);
		game->scene.menu[i] = NULL;
		i++;
	}
}

static void	start_game(t_game *game)
{
	clear_menu_images(game);
	init_camera(game);
	mlx_set_window_size(game->mlx, game->cam.cols * TILE_SIZE,
		game->cam.rows * TILE_SIZE + SCORE_BAR_HEIGHT);
	build_scene(game);
	mlx_key_hook(game->mlx, key_hook, game);
	if (!mlx_loop_hook(game->mlx, sign_blink_hook, game))
		fail(game, "failed to add loop hook");
}

static void	menu_key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(((t_game *) param)->mlx);
		return ;
	}
	start_game(param);
}

void	start_map_menu(t_game *game, const char *map_name)
{
	draw_menu_picture(game);
	draw_menu_text(game, map_name);
	mlx_key_hook(game->mlx, menu_key_hook, game);
	if (!mlx_loop_hook(game->mlx, menu_blink_hook, game))
		fail(game, "failed to add loop hook");
}
