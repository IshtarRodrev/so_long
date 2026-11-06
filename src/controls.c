/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:12:57 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:11 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

static int	setup_window(t_game *game)
{
	game->mlx = mlx_init(MENU_WIN_W, MENU_WIN_H, "so_long", false);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx, MENU_WIN_W, MENU_WIN_H);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (0);
	return (1);
}

void	init_game(t_game *game)
{
	if (!setup_window(game))
	{
		ft_printf("Error: failed to initialize window\n");
		exit(1);
	}
	load_player_sprites(game);
	load_exit_sprite(game);
	load_pattern_sprites(game);
	start_map_menu(game);
	mlx_loop(game->mlx);
}
