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

int	scan_maps_dir(t_game *game)
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

void	draw_map_list(t_game *game)
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
