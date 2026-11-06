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
