/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   map.c                                             :+:      :+:    :+:    */
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

// static void free_lines(char **lines, size_t count)
// {
//     size_t i;

//     if (!lines)
//         return;
//     i = 0;
//     while (i < count)
//     {
//         free(lines[i]);
//         i++;
//     }
//     free(lines);
// }

// static void strip_newline(char *line)
// {
//     size_t len;

//     if (!line)
//         return;
//     len = ft_strlen(line);
//     if (len > 0 && line[len - 1] == '\n')
//         line[len - 1] = '\0';
// }

// static int append_line(char ***lines, size_t rows, char *line)
// {
//     char **next;
//     size_t i;

//     next = malloc((rows + 2) * sizeof(char *));
//     if (!next)
//         return 0;
//     i = 0;
//     while (i < rows)
//     {
//         next[i] = (*lines)[i];
//         i++;
//     }
//     next[rows] = line;
//     next[rows + 1] = NULL;
//     free(*lines);
//     *lines = next;
//     return 1;
// }

/* int parse_map_file(const char *path, t_map *map)
{
int fd;
char *line;
char **lines;
size_t rows;

if (!path || !map)
return 0;
fd = open(path, O_RDONLY);
if (fd < 0)
{
ft_printf("Error: cannot open file '%s'\n", path);
return 0;
}
lines = NULL;
rows = 0;
while ((line = get_next_line(fd)))
{
strip_newline(line);
if (!append_line(&lines, rows, line))
{
free(line);
free_lines(lines, rows);
close(fd);
return 0;
}
rows++;
}
close(fd);
if (rows == 0)
{
free(lines);
return 0;
}
map->lines = lines;
map->rows = rows;
map->cols = ft_strlen(map->lines[0]);
map->player.x = -1;
map->player.y = -1;
map->collectibles = 0;
map->exits = 0;
return 1;
} */

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

static int	is_valid_tile(char t)
{
	return (t == '0' || t == '1' || t == 'C' || t == 'E' || t == 'P');
}

/* True if rows are non-empty, map->cols long and hold only valid tiles. */
static int	check_rows(const t_map *map)
{
	size_t	row;
	size_t	col;
	char	tile[2];

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
			if (!is_valid_tile(map->lines[row][col]))
			{
				tile[0] = map->lines[row][col];
				tile[1] = '\0';
				return (print_error("invalid character in map", tile), 0);
			}
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
