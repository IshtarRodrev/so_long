/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:40:22 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:19 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/* Prints why the search failed, if it did. Returns 1 if the path is valid. */
static int	report_path(t_path_search *s)
{
	if (s->leaked)
		return (map_error("map is not sealed, player can reach the edge"));
	if (s->found_collectibles != s->map->collectibles)
		return (map_error("not all collectibles are reachable"));
	if (s->found_exits < 1)
		return (map_error("exit is not reachable"));
	return (1);
}

/* Flood fill from P: every C and the exit must be reachable. */
int	path_is_valid(const t_map *map)
{
	t_path_search	s;

	if (!map || !map->lines)
		return (0);
	ft_bzero(&s, sizeof(s));
	s.map = map;
	s.visited = ft_calloc(map->rows * map->cols, sizeof(bool));
	s.queue = malloc(map->rows * map->cols * sizeof(int));
	if (!s.visited || !s.queue)
	{
		free(s.visited);
		free(s.queue);
		return (map_error("memory allocation failed"));
	}
	search_from_player(&s);
	free(s.visited);
	free(s.queue);
	return (report_path(&s));
}

/*
** The same flood fill from P, but keeps the result: true for every tile the
** player can reach. Returns NULL if memory runs out.
*/
bool	*reachable_tiles(const t_map *map)
{
	t_path_search	s;

	ft_bzero(&s, sizeof(s));
	s.map = map;
	s.visited = ft_calloc(map->rows * map->cols, sizeof(bool));
	s.queue = malloc(map->rows * map->cols * sizeof(int));
	if (!s.visited || !s.queue)
	{
		free(s.visited);
		free(s.queue);
		return (NULL);
	}
	search_from_player(&s);
	free(s.queue);
	return (s.visited);
}
