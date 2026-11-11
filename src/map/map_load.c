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
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/******************************************************************************/
/*								 PARAM HELPERS								  */
/******************************************************************************/

char	**load_and_validate(t_game *game, const char *path, t_map *parsed)
{
	char	**map;

	map = read_map_file(game, path);
	if (!map)
		return (NULL);
	parsed->lines = map;
	parsed->rows = (size_t) game->rows;
	parsed->cols = (size_t) game->cols;
	parsed->collectibles = 0;
	parsed->exits = 0;
	game->map = map;
	if (!validate_map(parsed) || !path_is_valid(game, parsed))
	{
		free_map(parsed);
		game->map = NULL;
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

/*
** The file to read for argument name: name itself if it can be opened
** (maps/x.ber, /abs/x.ber, x.ber in the current folder), else MAPS_DIR/name.
*/
static char	*map_path(const char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		return (ft_strdup(name));
	}
	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	return (ft_strjoin(MAPS_DIR "/", name));
}

/* Loads and validates the map file name (see map_path). Must end in .ber. */
char	**load_map(t_game *game, const char *name, t_map *parsed)
{
	char	*path;
	char	**map;

	if (!has_ber_extension(name))
		return (print_error("map file must have a .ber extension", name), NULL);
	path = map_path(name);
	if (!path)
		return (print_error("memory allocation failed", NULL), NULL);
	map = load_and_validate(game, path, parsed);
	free(path);
	return (map);
}
