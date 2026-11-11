/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
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

void	free_map(t_map *map)
{
	size_t	i;

	if (!map || !map->lines)
		return ;
	i = 0;
	while (i < map->rows)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	map->lines = NULL;
}

/* True if t is a map character; otherwise prints which one is invalid. */
static int	check_tile(char t)
{
	char	tile[2];

	if (t == '0' || t == '1' || t == 'C' || t == 'E' || t == 'P')
		return (1);
	tile[0] = t;
	tile[1] = '\0';
	print_error("invalid character in map", tile);
	return (0);
}

/* True if rows are non-empty, map->cols long and hold only valid tiles. */
static int	check_rows(const t_map *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < map->rows)
	{
		if (map->lines[row][0] == '\0')
			return (map_error("map contains an empty line"));
		if (ft_strlen(map->lines[row]) != map->cols)
			return (map_error("map rows must have equal width"));
		col = 0;
		while (col < map->cols)
		{
			if (!check_tile(map->lines[row][col]))
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

/* Counts collectibles and exits into map, finds the player, returns players. */
static int	count_tiles(t_map *map)
{
	size_t	i;
	int		players;
	char	tile;

	players = 0;
	i = 0;
	while (i < map->rows * map->cols)
	{
		tile = map->lines[i / map->cols][i % map->cols];
		if (tile == 'P')
		{
			players++;
			map->player.x = (int)(i % map->cols);
			map->player.y = (int)(i / map->cols);
		}
		else if (tile == 'C')
			map->collectibles++;
		else if (tile == 'E')
			map->exits++;
		i++;
	}
	return (players);
}

int	validate_map(const t_map *map)
{
	if (!map || !map->lines || !check_rows(map))
		return (0);
	if (map->rows < 3 || map->cols < 3)
		return (map_error("map is too small"));
	if (count_tiles((t_map *) map) != 1)
		return (map_error("map must contain exactly one player ('P')"));
	if (map->collectibles < 1)
		return (map_error("map must contain at least one collectible ('C')"));
	if (map->exits < 1)
		return (map_error("map must contain an exit ('E')"));
	if (map->exits > 1)
		return (map_error("map must contain only one exit ('E')"));
	return (1);
}
