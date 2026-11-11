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

void	init_progress(t_game *game, const t_map *parsed)
{
	game->progress.collected = ft_calloc(parsed->rows * parsed->cols,
			sizeof(bool));
	if (!game->progress.collected)
		fail(game, "memory allocation failed");
	game->progress.player = parsed->player;
	game->progress.collectibles_left = parsed->collectibles;
	game->progress.collectibles_total = parsed->collectibles;
	pick_collectibles(game);
}

bool	is_collected(t_game *game, int x, int y)
{
	return (game->progress.collected[tile_index(game, x, y)]);
}

void	collect_tile(t_game *game, int x, int y)
{
	game->progress.collected[tile_index(game, x, y)] = true;
	game->progress.collectibles_left--;
	uncover_tile(game, x, y);
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
