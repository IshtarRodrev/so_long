/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
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

char	**load_and_validate(t_game *game, const char *path, t_lay *lay)
{
	char	**map;

	map = read_map_file(game, path);
	if (!map)
	{
		ft_printf("Error: cannot open or read map file '%s'\n", path);
		return (NULL);
	}
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

/* Loads and validates maps/<map_name>.ber. */
char	**load_map_by_name(t_game *game, const char *map_name, t_lay *lay)
{
	char	*tmp;
	char	*path;
	char	**map;

	tmp = ft_strjoin(MAPS_DIR "/", map_name);
	path = NULL;
	if (tmp)
		path = ft_strjoin(tmp, ".ber");
	free(tmp);
	if (!path)
	{
		ft_printf("Error: memory allocation failed\n");
		return (NULL);
	}
	map = load_and_validate(game, path, lay);
	free(path);
	return (map);
}
