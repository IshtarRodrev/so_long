/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <sys/time.h>

/* xorshift32: a small pseudo-random generator. state must never be 0. */
static uint32_t	next_random(uint32_t *state)
{
	*state ^= *state << 13;
	*state ^= *state >> 17;
	*state ^= *state << 5;
	return (*state);
}

/* A seed that differs on every run: the current time in microseconds. */
static uint32_t	random_seed(void)
{
	struct timeval	now;
	uint32_t		seed;
	int				i;

	gettimeofday(&now, NULL);
	seed = ((uint32_t) now.tv_sec * 1000003u) ^ (uint32_t) now.tv_usec;
	if (seed == 0)
		seed = 1;
	i = 0;
	while (i++ < 8)
		next_random(&seed);
	return (seed);
}

/*
** Keeps at most MAX_COLLECTIBLES collectibles to do, chosen at random; the
** others start completed. Each C tile is kept with probability need / left,
** which picks exactly need tiles, every choice equally likely.
*/
void	pick_collectibles(t_game *game)
{
	uint32_t	state;
	int			need;
	int			left;
	int			i;

	left = game->progress.collectibles_total;
	need = left;
	if (need > MAX_COLLECTIBLES)
		need = MAX_COLLECTIBLES;
	game->progress.collectibles_total = need;
	game->progress.collectibles_left = need;
	state = random_seed();
	i = -1;
	while (++i < game->rows * game->cols)
	{
		if (game->map[i / game->cols][i % game->cols] == 'C')
		{
			if ((int)(next_random(&state) % (uint32_t) left) < need)
				need--;
			else
				game->progress.collected[i] = true;
			left--;
		}
	}
}
