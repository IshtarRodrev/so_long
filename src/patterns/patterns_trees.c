/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_trees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/* True if (x, y) keeps a tree away: a wall or another tree. */
static bool	blocks_tree(t_game *game, bool *trees, int x, int y)
{
	if (!in_map(game, x, y))
		return (false);
	return (game->map[y][x] == '1' || trees[tile_index(game, x, y)]);
}

/* True if no wall or tree is closer than TREE_SPACING to (mx, my). */
static bool	tree_fits(t_game *game, bool *trees, int mx, int my)
{
	int	dx;
	int	dy;

	dy = -(TREE_SPACING - 1);
	while (dy < TREE_SPACING)
	{
		dx = -(TREE_SPACING - 1);
		while (dx < TREE_SPACING)
		{
			if (blocks_tree(game, trees, mx + dx, my + dy))
				return (false);
			dx++;
		}
		dy++;
	}
	return (true);
}

/*
** True for every tile that shows a tree: unreachable floor (inside or
** outside) at least TREE_SPACING tiles from every wall and every other tree.
** The map edge does not count. Planted row by row. Returns NULL if memory runs
** out.
*/
bool	*tree_tiles(t_game *game)
{
	bool	*trees;
	int		i;
	int		x;
	int		y;

	trees = ft_calloc((size_t) game->rows * game->cols, sizeof(bool));
	if (!trees)
		return (NULL);
	i = 0;
	while (i < game->rows * game->cols)
	{
		x = i % game->cols;
		y = i / game->cols;
		if (game->map[y][x] == '0' && !game->reachable[i]
			&& tree_fits(game, trees, x, y))
			trees[i] = true;
		i++;
	}
	return (trees);
}
