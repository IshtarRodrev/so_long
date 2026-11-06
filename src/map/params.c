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

/******************************************************************************/
/*								 PARAM HELPERS								  */
/******************************************************************************/

int	has_valid_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".ber", 4) == 0);
}

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
