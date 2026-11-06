/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:28 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 20:50:24 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <dirent.h>
#include <stdlib.h>

/******************************************************************************/
/*								MENU KEY HOOK								  */
/******************************************************************************/

static int	key_to_index(mlx_key_data_t keydata)
{
	if (keydata.key >= MLX_KEY_1 && keydata.key <= MLX_KEY_9)
		return (keydata.key - MLX_KEY_1);
	return (-1);
}

static void	try_select_map(t_game *game, int index)
{
	t_lay	lay;
	char	**map;

	map = load_and_validate(game, game->map_names[index], &lay);
	if (!map)
	{
		show_status(game, "Error: map validation fail (see terminal)");
		return ;
	}
	progress_init(game, &lay);
	start_game(game, map);
}

static void	menu_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		index;

	game = param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	index = key_to_index(keydata);
	if (index >= 0 && index < game->map_count)
		try_select_map(game, index);
}

/******************************************************************************/
/*								 PUBLIC ENTRY								  */
/******************************************************************************/

void	start_map_menu(t_game *game)
{
	if (!scan_maps_dir(game))
	{
		ft_printf("Error: no '.ber' maps found in '%s'\n", MAPS_DIR);
		exit(1);
	}
	draw_map_list(game);
	mlx_key_hook(game->mlx, menu_key_hook, game);
}
