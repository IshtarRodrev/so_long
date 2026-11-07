/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:33 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:40:35 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/******************************************************************************/
/*								 PARAM HELPERS								  */
/******************************************************************************/

char	**load_and_validate(t_game *game, const char *path, t_map *lay)
{
	char	**map;

	map = read_map_file(game, path);
	if (!map)
		return (NULL);
	lay->lines = map;
	lay->rows = (size_t) game->rows;
	lay->cols = (size_t) game->cols;
	lay->collectibles = 0;
	lay->exits = 0;
	if (!validate_map(lay) || !path_is_valid(lay))
	{
		free_map(lay);
		return (NULL);
	}
	return (map);
}

/* True if path names a file that ends in ".ber" and has a name before it. */
static int	has_ber_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".ber", 4) != 0)
		return (0);
	return (path[len - 5] != '/');
}

/* Loads and validates the map file MAPS_DIR/<name>. name must end in .ber. */
char	**load_map(t_game *game, const char *name, t_map *lay)
{
	char	*path;
	char	**map;

	if (!has_ber_extension(name))
		return (print_error("map file must have a .ber extension", name), NULL);
	path = ft_strjoin(MAPS_DIR "/", name);
	if (!path)
		return (print_error("memory allocation failed", NULL), NULL);
	map = load_and_validate(game, path, lay);
	free(path);
	return (map);
}
