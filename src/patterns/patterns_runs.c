/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_runs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:42:56 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/*
** A kitchen starts with a water cooler and a coffee machine, and ends with a
** fridge, or two fridges if it is longer than 7. Every tile in between is a
** kitchen tile.
*/

static mlx_texture_t	*kitchen_part_texture(t_game *game, int index,
	int length, int face)
{
	if (index == 0)
		return (game->water_cooler_tex[face]);
	if (index == 1)
		return (game->coffee_tex[face]);
	if (index == length - 1 || (length > 7 && index == length - 2))
		return (game->fridge_tex[face]);
	return (game->kitchen_tex[face]);
}

/* True if a straight run with these two ends and this length is equipment. */

bool	is_equipment_run(char first, char last, int length)
{
	if (first == '1' && last == '1')
		return (length >= 2);
	if (first == '0' && last == '0')
		return (length >= 4);
	return (length == 2 && (first == '1' || last == '1')
		&& (first == '0' || last == '0'));
}

/* Which sprite a straight run of collectibles gets, given what is at its two ends. */
mlx_texture_t	*run_texture(t_game *game, t_run run, int face)
{
	if (!is_equipment_run(run.first, run.last, run.length))
		return (NULL);
	if (run.first == '1' && run.last == '1' && run.length == 2)
		return (game->sink_tex[face]);
	if (run.first == '1' && run.last == '1' && run.length == 3)
		return (game->toilet_tex[face]);
	if (run.first == '1' && run.last == '1')
		return (game->lockers_tex[face]);
	if (run.length == 2)
		return (game->vending_tex[face]);
	return (kitchen_part_texture(game, run.index, run.length, face));
}
