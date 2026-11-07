/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:12:57 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:11 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static int	setup_window(t_game *game)
{
	game->mlx = mlx_init(WINDOW_W, WINDOW_H, "so_long", false);
	if (!game->mlx)
		return (0);
	return (1);
}

void	init_game(t_game *game, const char *map_name)
{
	t_map	lay;

	game->map = load_map(game, map_name, &lay);
	if (!game->map)
		exit_game(game, 1);
	init_progress(game, &lay);
	init_patterns(game, &lay);
	if (!setup_window(game))
		fail(game, "failed to initialize window");
	load_player_sprites(game);
	load_exit_sprite(game);
	load_pattern_sprites(game);
	start_map_menu(game, map_name);
	mlx_loop(game->mlx);
	free_game(game);
}
