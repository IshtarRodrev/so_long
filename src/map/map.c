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

/* Prints "Error: <msg>" on its own line. Always returns 0. */
static int	map_error(const char *msg)
{
	ft_printf("Error: %s\n", msg);
	return (0);
}

/* True if every row is map->cols long and holds only valid tiles. */
static int	check_rows(const t_map *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < map->rows)
	{
		if (ft_strlen(map->lines[row]) != map->cols)
			return (map_error("map rows must have equal width"));
		col = 0;
		while (col < map->cols)
		{
			if (!is_valid_tile(map->lines[row][col]))
			{
				ft_printf("Error: invalid character '%c' in map\n",
					map->lines[row][col]);
				return (0);
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
	if (!map || !map->lines || map->rows < 3 || map->cols < 3)
		return (map_error("map is too small"));
	if (!check_rows(map))
		return (0);
	if (count_tiles((t_map *) map) != 1)
		return (map_error("map must contain exactly one player ('P')"));
	if (map->collectibles < 1)
		return (map_error("map must contain at least one collectible ('C')"));
	if (map->exits < 1)
		return (map_error("map must contain at least one exit ('E')"));
	return (1);
}

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
static void	search_from_player(t_path_search *s)
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
static int	collectible_is_trapped(t_path_search *s)
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

/* Prints why the search failed, if it did. Returns 1 if the path is valid. */
static int	report_path(t_path_search *s, int trapped)
{
	if (s->leaked)
		return (map_error("map is not sealed, player can reach the edge"));
	if (s->found_collectibles != s->map->collectibles)
		return (map_error("not all collectibles are reachable"));
	if (s->found_exits < 1)
		return (map_error("exit is not reachable"));
	if (trapped)
		return (map_error("a collectible leads to an area the player "
				"can't leave"));
	return (1);
}

int	path_is_valid(const t_map *map) //TODO: replace with flood fill
{
	t_path_search	s;
	int				trapped;

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
	trapped = collectible_is_trapped(&s);
	free(s.visited);
	free(s.queue);
	return (report_path(&s, trapped));
}

/* Cuts the line at its newline, and drops a '\r' before it (Windows files). */
static void	strip_line_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = '\0';
	if (i > 0 && line[i - 1] == '\r')
		line[i - 1] = '\0';
}

/* Reads every line of fd into a NULL-terminated array and counts them. */
static char	**read_lines(int fd, int *rows)
{
	char	*line;
	char	**map;

	map = NULL;
	*rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_line_end(line);
		if (*rows == 0)
			map = malloc(sizeof(char *) * 2);
		else
			map = realloc(map, sizeof(char *) * (*rows + 2));
		if (!map)
			return (NULL);
		map[*rows] = line;
		map[*rows + 1] = NULL;
		(*rows)++;
		line = get_next_line(fd);
	}
	return (map);
}

char	**read_map_file(t_game *game, const char *path)
{
	int		fd;
	int		rows;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = read_lines(fd, &rows);
	close(fd);
	if (!map)
		return (NULL);
	game->rows = rows;
	game->cols = (int) ft_strlen(map[0]);
	return (map);
}
