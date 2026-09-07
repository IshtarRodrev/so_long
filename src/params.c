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

char	**load_and_validate(const char *path, t_lay *lay)
{
	char	**map;

	map = read_map_file(path);
	if (!map)
	{
		ft_printf("Error: cannot open or read map file '%s'\n", path);
		return (NULL);
	}
	lay->lines = map;
	lay->rows = (size_t)g_game.rows;
	lay->cols = (size_t)g_game.cols;
	lay->collectibles = 0;
	lay->exits = 0;
	if (!validate_map(lay) || !path_is_valid(lay))
	{
		free_map(lay);
		return (NULL);
	}
	return (map);
}
