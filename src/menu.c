/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:28 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:21 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/* Shows the map name (no directories, no .ber) and how to start or quit. */
static void	draw_menu(t_game *game, const char *map_name)
{
	char	*label;

	if (ft_strrchr(map_name, '/'))
		map_name = ft_strrchr(map_name, '/') + 1;
	label = ft_strjoin("Map: ", map_name);
	if (!label)
	{
		print_error("memory allocation failed", NULL);
		exit(1);
	}
	label[ft_strlen(label) - 4] = '\0';
	game->menu_imgs[0] = mlx_put_string(game->mlx, label, 40, 40);
	free(label);
	game->menu_imgs[1] = mlx_put_string(game->mlx,
			"Press any key to start or ESC to exit", 40, 80);
}

static void	clear_menu_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < MENU_LINES)
	{
		if (game->menu_imgs[i])
			mlx_delete_image(game->mlx, game->menu_imgs[i]);
		game->menu_imgs[i] = NULL;
		i++;
	}
}

static void	start_game(t_game *game)
{
	clear_menu_images(game);
	init_camera(game);
	mlx_set_window_size(game->mlx, game->view_cols * TILE_SIZE,
		game->view_rows * TILE_SIZE + SCORE_BAR_HEIGHT);
	build_scene(game);
	mlx_key_hook(game->mlx, key_hook, game);
}

static void	menu_key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	start_game(param);
}

void	start_map_menu(t_game *game, const char *map_name)
{
	draw_menu(game, map_name);
	mlx_key_hook(game->mlx, menu_key_hook, game);
}
