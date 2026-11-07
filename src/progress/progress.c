/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:13:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:42:04 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

void	init_progress(t_game *game, const t_map *lay)
{
	game->progress.collected = ft_calloc(lay->rows * lay->cols, sizeof(bool));
	if (!game->progress.collected)
		fail(game, "memory allocation failed");
	game->progress.player = lay->player;
	game->progress.collectibles_left = lay->collectibles;
	game->progress.collectibles_total = lay->collectibles;
	pick_collectibles(game);
}

bool	is_collected(t_game *game, int mx, int my)
{
	return (game->progress.collected[tile_index(game, mx, my)]);
}

void	collect_tile(t_game *game, int mx, int my)
{
	game->progress.collected[tile_index(game, mx, my)] = true;
	game->progress.collectibles_left--;
	uncover_tile(game, mx, my);
}

/*
** Colour of the progress bar: red with nothing done, yellow at half, green
** when every task is done (orange lies between red and yellow).
*/
uint32_t	progress_color(t_game *game)
{
	int	step;
	int	red;
	int	green;

	step = 510 * (game->progress.collectibles_total
			- game->progress.collectibles_left)
		/ game->progress.collectibles_total;
	red = 255;
	green = step;
	if (step > 255)
	{
		red = 510 - step;
		green = 255 - (step - 255) * 55 / 255;
	}
	return (((uint32_t) red << 24) | ((uint32_t) green << 16) | 0xFF);
}
