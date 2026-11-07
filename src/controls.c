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
	return (1);
}

void	init_game(t_game *game, const char *map_name)
{
	t_lay	lay;

	game->map = load_map_by_name(game, map_name, &lay);
	if (!game->map)
		exit(1);
	progress_init(game, &lay);
	if (!setup_window(game))
	{
		print_error("failed to initialize window", NULL);
		exit(1);
	}
	load_player_sprites(game);
	load_exit_sprite(game);
	load_pattern_sprites(game);
	start_map_menu(game, map_name);
	mlx_loop(game->mlx);
}
