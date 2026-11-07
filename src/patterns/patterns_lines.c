/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:42:56 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/*
** Which way the row from start to end on line my faces: down if walls run all
** along above it and floor all along below it, up if the other way round, or
** -1 if neither.
*/

static int	row_face(t_game *game, int start, int end, int my)
{
	char	above;
	char	below;

	above = tile_at(game, start, my - 1);
	below = tile_at(game, start, my + 1);
	while (start <= end)
	{
		if (tile_at(game, start, my - 1) != above
			|| tile_at(game, start, my + 1) != below)
			return (-1);
		start++;
	}
	if (above == '1' && below == '0')
		return (FACE_DOWN);
	if (above == '0' && below == '1')
		return (FACE_UP);
	return (-1);
}

/*
** Which way the column from start to end on line mx faces: right if walls run
** all along its left and floor all along its right, left if the other way
** round, or -1 if neither.
*/

static int	column_face(t_game *game, int start, int end, int mx)
{
	char	left;
	char	right;

	left = tile_at(game, mx - 1, start);
	right = tile_at(game, mx + 1, start);
	while (start <= end)
	{
		if (tile_at(game, mx - 1, start) != left
			|| tile_at(game, mx + 1, start) != right)
			return (-1);
		start++;
	}
	if (left == '1' && right == '0')
		return (FACE_RIGHT);
	if (left == '0' && right == '1')
		return (FACE_LEFT);
	return (-1);
}

/*
** True if the column at (mx, my) is 2 or more collectibles with walls along one
** long side and floor along the other, and is equipment. Gives its sprite, which
** is NULL if the picture is missing. It faces the floor: right if the wall is on
** the left, left if the wall is on the right.
*/

bool	column_sprite(t_game *game, int mx, int my, mlx_texture_t **sprite)
{
	int		start;
	int		end;
	int		face;
	t_run	run;

	start = my;
	while (tile_at(game, mx, start - 1) == 'C')
		start--;
	end = my;
	while (tile_at(game, mx, end + 1) == 'C')
		end++;
	face = column_face(game, start, end, mx);
	if (face < 0)
		return (false);
	run.first = tile_at(game, mx, start - 1);
	run.last = tile_at(game, mx, end + 1);
	run.index = my - start;
	run.length = end - start + 1;
	*sprite = run_texture(game, run, face);
	return (is_equipment_run(run.first, run.last, run.length));
}

/*
** Returns the sprite for a row of collectibles with walls along one long side
** and floor along the other, or NULL if the row at (mx, my) is not like that.
** Walls at both ends: 2 long is sinks, 3 long is toilets, longer is lockers.
** Wall at one end and floor at the other: 2 long is vending machines.
** Floor at both ends: 4 or more long is a kitchen, starting from the left.
** A row faces the floor: down if the wall is above it, up if the wall is below.
*/

mlx_texture_t	*row_texture(t_game *game, int mx, int my)
{
	int		start;
	int		end;
	int		face;
	t_run	run;

	start = mx;
	while (tile_at(game, start - 1, my) == 'C')
		start--;
	end = mx;
	while (tile_at(game, end + 1, my) == 'C')
		end++;
	face = row_face(game, start, end, my);
	if (face < 0)
		return (NULL);
	run.first = tile_at(game, start - 1, my);
	run.last = tile_at(game, end + 1, my);
	run.index = mx - start;
	run.length = end - start + 1;
	return (run_texture(game, run, face));
}
