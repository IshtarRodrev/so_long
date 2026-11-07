/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:13:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:42:04 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

void	progress_init(t_game *game, const t_lay *lay)
{
	game->progress.collected = ft_calloc(lay->rows * lay->cols, sizeof(bool));
	game->cover = ft_calloc(lay->rows * lay->cols, sizeof(int));
	if (!game->progress.collected || !game->cover)
	{
		print_error("memory allocation failed", NULL);
		exit(1);
	}
	game->progress.player = lay->player;
	game->progress.collectibles_left = lay->collectibles;
	game->progress.collectibles_total = lay->collectibles;
}

bool	is_collected(t_game *game, int mx, int my)
{
	return (game->progress.collected[(size_t) my * game->cols + mx]);
}

void	collect_tile(t_game *game, int mx, int my)
{
	game->progress.collected[(size_t) my * game->cols + mx] = true;
	game->progress.collectibles_left--;
	uncover_tile(game, mx, my);
}
