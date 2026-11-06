/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_transition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:28 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:21 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <dirent.h>
#include <stdlib.h>

void	show_status(t_game *game, const char *msg)
{
	if (game->status_img)
	{
		mlx_delete_image(game->mlx, game->status_img);
		game->status_img = NULL;
	}
	game->status_img = mlx_put_string(game->mlx, msg, 40,
			80 + game->map_count * 30 + 30);
}

/******************************************************************************/
/*								   TRANSITION								  */
/******************************************************************************/

static void	clear_menu_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->menu_img_count)
	{
		mlx_delete_image(game->mlx, game->menu_imgs[i]);
		i++;
	}
	game->menu_img_count = 0;
	if (game->status_img)
	{
		mlx_delete_image(game->mlx, game->status_img);
		game->status_img = NULL;
	}
}

static void	free_map_names(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_count)
	{
		free(game->map_names[i]);
		i++;
	}
	game->map_count = 0;
}

void	start_game(t_game *game, char **map)
{
	clear_menu_images(game);
	free_map_names(game);
	game->map = map;
	init_camera(game);
	mlx_set_window_size(game->mlx, game->view_cols * TILE_SIZE,
		game->view_rows * TILE_SIZE + SCORE_BAR_HEIGHT);
	mlx_resize_image(game->img, game->view_cols * TILE_SIZE,
		game->view_rows * TILE_SIZE + SCORE_BAR_HEIGHT);
	render_map(game);
	mlx_key_hook(game->mlx, key_hook, game);
}
