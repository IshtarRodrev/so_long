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
#include <dirent.h>
#include <stdlib.h>

#define MAPS_DIR "maps"

/******************************************************************************/
/*								MAP LIST SCAN								  */
/******************************************************************************/

static char	*build_map_path(const char *fname)
{
	return (ft_strjoin(MAPS_DIR "/", fname));
}

static int	add_map_name(t_game *game, const char *fname)
{
	char	*path;

	path = build_map_path(fname);
	if (!path)
		return (0);
	game->map_names[game->map_count++] = path;
	return (1);
}

static int	scan_maps_dir(t_game *game)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(MAPS_DIR);
	if (!dir)
		return (0);
	game->map_count = 0;
	entry = readdir(dir);
	while (entry && game->map_count < MENU_MAX_MAPS)
	{
		if (has_valid_extension(entry->d_name)
			&& !add_map_name(game, entry->d_name))
		{
			closedir(dir);
			return (0);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (game->map_count > 0);
}

/******************************************************************************/
/*								MENU RENDERING								  */
/******************************************************************************/

static char	*build_entry_label(t_game *game, int index)
{
	char	*num;
	char	*tmp;
	char	*label;

	num = ft_itoa(index + 1);
	if (!num)
		return (NULL);
	tmp = ft_strjoin(num, " ");
	free(num);
	if (!tmp)
		return (NULL);
	label = ft_strjoin(tmp, game->map_names[index]);
	free(tmp);
	return (label);
}

static void	draw_map_list(t_game *game)
{
	int			i;
	char		*label;
	mlx_image_t	*img;

	game->menu_imgs[game->menu_img_count++] = mlx_put_string(game->mlx,
			"so_long - choose a map (press 1-9, ESC to quit):", 40, 40);
	i = 0;
	while (i < game->map_count)
	{
		label = build_entry_label(game, i);
		if (label)
		{
			img = mlx_put_string(game->mlx, label, 40, 80 + i * 30);
			game->menu_imgs[game->menu_img_count++] = img;
			free(label);
		}
		i++;
	}
}

static void	show_status(t_game *game, const char *msg)
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

static void	start_game(t_game *game, char **map)
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
		show_status(game, "Error: that map failed validation (see terminal) - pick another");
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
