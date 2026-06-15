#include "libft.h"
#include "so_long.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

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

void free_map(t_map *map)
{
	size_t i;

	if (!map || !map->lines)
		return;
	i = 0;
	while (i < map->rows)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	map->lines = NULL;
}

static int is_valid_tile(char t)
{
	return (t == '0' || t == '1' || t == 'C' || t == 'E' || t == 'P');
}

int validate_map(const t_map *map)
{
	size_t row;
	size_t col;
	int player_count;

	if (!map || !map->lines || map->rows < 3 || map->cols < 3)
	{
		ft_printf("Error: map is too small\n");
		return 0;
	}
	player_count = 0;
	row = 0;
	while (row < map->rows)
	{
/* FIXME: the map must be rectangular, not just square!!
        if (ft_strlen(map->lines[row]) != map->cols)
        {
            ft_printf("Error: map rows must have equal width\n");
            return 0;
        } */
        col = 0;
        while (col < map->cols)
        {
            char tile;

            tile = map->lines[row][col];
            if (!is_valid_tile(tile))
            {
                ft_printf("Error: invalid character '%c' in map\n", tile);
                return 0;
            }
            if (row == 0 || row == map->rows - 1 || col == 0 || col == map->cols - 1)
            {
                if (tile != '1')
                {
                    ft_printf("Error: map border must be walls ('1')\n");
                    return 0;
                }
            }
            if (tile == 'P')
            {
                player_count++;
                ((t_map *)map)->player.x = (int)col;
                ((t_map *)map)->player.y = (int)row;
            }
            else if (tile == 'C')
                ((t_map *)map)->collectibles++;
            else if (tile == 'E')
                ((t_map *)map)->exits++;
            col++;
        }
        row++;
    }
    if (player_count != 1)
    {
        ft_printf("Error: map must contain exactly one player ('P')\n");
        return 0;
    }
    if (map->collectibles < 1)
    {
        ft_printf("Error: map must contain at least one collectible ('C')\n");
        return 0;
    }
    if (map->exits < 1)
    {
        ft_printf("Error: map must contain at least one exit ('E')\n");
        return 0;
    }
    return 1;
}

int path_is_valid(const t_map *map) //TODO: replace with flood fill
{
    size_t total;
    bool *visited;
    int *queue;
    size_t qstart;
    size_t qend;
    int found_collectibles;
    int found_exits;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    if (!map || !map->lines)
        return 0;
    total = map->rows * map->cols;
    visited = ft_calloc(total, sizeof(bool));
    queue = malloc(total * sizeof(int));
    if (!visited || !queue)
    {
        free(visited);
        free(queue);
        ft_printf("Error: memory allocation failed\n");
        return 0;
    }
    qstart = 0;
    qend = 0;
    found_collectibles = 0;
    found_exits = 0;
    queue[qend++] = map->player.y * (int)map->cols + map->player.x;
    visited[queue[0]] = true;
    while (qstart < qend)
    {
        int index;
        int y;
        int x;

        index = queue[qstart++];
        y = index / (int)map->cols;
        x = index % (int)map->cols;
        if (map->lines[y][x] == 'C')
            found_collectibles++;
        else if (map->lines[y][x] == 'E')
            found_exits++;
        int i;

        i = 0;
        while (i < 4)
        {
            int nx;
            int ny;
            int nindex;

            nx = x + directions[i][0];
            ny = y + directions[i][1];
            if (ny < 0 || ny >= (int)map->rows || nx < 0 || nx >= (int)map->cols)
            {
                i++;
                continue;
            }
            nindex = ny * (int)map->cols + nx;
            if (visited[nindex] || map->lines[ny][nx] == '1')
            {
                i++;
                continue;
            }
            visited[nindex] = true;
            queue[qend++] = nindex;
            i++;
        }
    }
    free(visited);
    free(queue);
    if (found_collectibles != map->collectibles)
    {
        ft_printf("Error: not all collectibles are reachable\n");
        return 0;
    }
    if (found_exits < 1)
    {
        ft_printf("Error: exit is not reachable\n");
        return 0;
    }
    return 1;
}
char **read_map_file(const char *path)
{
    int fd;
    char *line;
    char **map;
    int rows;
    int i;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    map = NULL;
    rows = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        i = 0;
        while (line[i] != '\0' && line[i] != '\n')
            i++;
        if (line[i] == '\n')
            line[i] = '\0';
        if (rows == 0)
            map = malloc(sizeof(char *) * 2);
        else
            map = realloc(map, sizeof(char *) * (rows + 2));
        if (!map)
            return (NULL);
        map[rows] = line;
        map[rows + 1] = NULL;
        rows++;
    }
    close(fd);
    if (rows == 0)
        return (NULL);
    g_game.rows = rows;
    g_game.cols = (int)ft_strlen(map[0]);
    return (map);
}
