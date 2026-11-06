/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   map_path.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: akechedz <akechedz@student.42heilbronn.de>#+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/06 17:40:22 by akechedz         #+#    #+#              */
/*   Updated: 2026/11/06 17:41:19 by akechedz        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	is_map_edge(const t_map *map, int y, int x)
{
	return (y == 0 || y == (int) map->rows - 1
		|| x == 0 || x == (int) map->cols - 1);
}

/* Queues the tile at (x, y) if it is in the map, not a wall and not seen. */
static void	queue_tile(t_path_search *s, int x, int y)
{
	int	index;

	if (y < 0 || y >= (int) s->map->rows || x < 0 || x >= (int) s->map->cols)
		return ;
	index = y * (int) s->map->cols + x;
	if (s->visited[index] || s->map->lines[y][x] == '1')
		return ;
	s->visited[index] = true;
	if (is_map_edge(s->map, y, x))
		s->leaked = 1;
	s->queue[s->qend++] = index;
}

/* Walks every tile the player can reach. Collectibles and exits end a path. */
void	search_from_player(t_path_search *s)
{
	size_t	next;
	int		x;
	int		y;
	char	tile;

	queue_tile(s, s->map->player.x, s->map->player.y);
	next = 0;
	while (next < s->qend)
	{
		x = s->queue[next] % (int) s->map->cols;
		y = s->queue[next] / (int) s->map->cols;
		next++;
		tile = s->map->lines[y][x];
		if (tile == 'C')
			s->found_collectibles++;
		else if (tile == 'E')
			s->found_exits++;
		else
		{
			queue_tile(s, x + 1, y);
			queue_tile(s, x - 1, y);
			queue_tile(s, x, y + 1);
			queue_tile(s, x, y - 1);
		}
	}
}

/* True if (x, y) is in the map, not a wall, and the search never got there. */
static int	is_unreached(t_path_search *s, int x, int y)
{
	return (y >= 0 && y < (int) s->map->rows && x >= 0
		&& x < (int) s->map->cols && s->map->lines[y][x] != '1'
		&& !s->visited[y * (int) s->map->cols + x]);
}

/* True if a reached collectible opens onto tiles the player can't get to. */
int	collectible_is_trapped(t_path_search *s)
{
	size_t	i;
	int		x;
	int		y;

	i = 0;
	while (i < s->qend)
	{
		x = s->queue[i] % (int) s->map->cols;
		y = s->queue[i] / (int) s->map->cols;
		i++;
		if (s->map->lines[y][x] == 'C' && (is_unreached(s, x + 1, y)
				|| is_unreached(s, x - 1, y) || is_unreached(s, x, y + 1)
				|| is_unreached(s, x, y - 1)))
			return (1);
	}
	return (0);
}
