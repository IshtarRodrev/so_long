/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   map_read.c                                        :+:      :+:    :+:    */
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

/*
** On allocation failure: frees the *rows lines of map, map itself and line,
** reports the error and sets *rows to -1. Returns NULL.
*/
static char	**free_lines(char **map, int *rows, char *line)
{
	while (*rows > 0)
		free(map[--(*rows)]);
	free(map);
	free(line);
	*rows = -1;
	print_error("memory allocation failed", NULL);
	return (NULL);
}

/* Reads every line of fd into a NULL-terminated array and counts them. */
static char	**read_lines(int fd, int *rows)
{
	char	*line;
	char	**map;
	char	**grown;

	map = NULL;
	*rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_line_end(line);
		grown = ft_realloc(map, sizeof(char *) * (*rows + 1),
				sizeof(char *) * (*rows + 2));
		if (!grown)
			return (free_lines(map, rows, line));
		map = grown;
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

	fd = open(path, O_RDONLY | O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (print_error("map file is a directory", path), NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error("cannot open map file", path), NULL);
	map = read_lines(fd, &rows);
	close(fd);
	if (!map && rows == 0)
		print_error("map file is empty", path);
	if (!map)
		return (NULL);
	game->rows = rows;
	game->cols = (int) ft_strlen(map[0]);
	return (map);
}
