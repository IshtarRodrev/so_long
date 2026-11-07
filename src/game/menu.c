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

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/*
** Shows the map name (no directories, no .ber) and how to start or quit in
** the bottom right corner, 40 px from the right and the bottom border.
*/
static void	draw_menu(t_game *game, const char *map_name)
{
	char	*label;

	if (ft_strrchr(map_name, '/'))
		map_name = ft_strrchr(map_name, '/') + 1;
	label = ft_strjoin("Map: ", map_name);
	if (!label)
		fail(game, "memory allocation failed");
	label[ft_strlen(label) - 4] = '\0';
	game->scene.menu[0] = mlx_put_string(game->mlx, label, 0, 40);
	free(label);
	game->scene.menu[1] = mlx_put_string(game->mlx,
			"Press any key to start or ESC to exit", 0, 80);
	if (!game->scene.menu[0] || !game->scene.menu[1])
		fail(game, "failed to create image");
	game->scene.menu[0]->instances[0].x = WINDOW_W - 40
		- (int) game->scene.menu[0]->width;
	game->scene.menu[1]->instances[0].x = WINDOW_W - 40
		- (int) game->scene.menu[1]->width;
	game->scene.menu[1]->instances[0].y = WINDOW_H - 40
		- (int) game->scene.menu[1]->height;
	game->scene.menu[0]->instances[0].y = game->scene.menu[1]->instances[0].y
		- 40;
}

static void	clear_menu_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < MENU_LINES)
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
	draw_menu(game, map_name);
	mlx_key_hook(game->mlx, menu_key_hook, game);
}
