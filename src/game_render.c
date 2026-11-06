/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   game_render.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: akechedz <akechedz@student.42heilbronn.de>#+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/06 17:48:30 by akechedz         #+#    #+#              */
/*   Updated: 2026/11/06 17:49:12 by akechedz        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char	*dir_name(int d)
{
	if (d == DIR_BACK)
		return ("back");
	if (d == DIR_LEFT)
		return ("left");
	if (d == DIR_RIGHT)
		return ("right");
	return ("front");
}

int	tile_color(char tile)
{
	if (tile == '1')
		return (0xE8E8E8);
	if (tile == 'C')
		return (0xFFD700);
	if (tile == 'E')
		return (0x32CD32);
	return (0x505050);
}

static char	*sprite_path(const char *dir_name, int frame)
{
	char	buf[128];

	snprintf(buf, sizeof(buf), "%s/%s_%02d.png", SPRITE_DIR, dir_name, frame);
	return (ft_strdup(buf));
}

static void	load_direction_sprites(t_game *game, int d)
{
	int		f;
	char	*path;

	f = 0;
	while (f < SPRITE_FRAMES)
	{
		path = sprite_path(dir_name(d), f + 1);
		if (access(path, F_OK) != 0)
		{
			free(path);
			break ;
		}
		game->player_tex[d][f] = mlx_load_png(path);
		free(path);
		if (!game->player_tex[d][f])
		{
			ft_printf("Error: failed to load player sprite\n");
			exit(1);
		}
		f++;
	}
	game->player_frame_count[d] = f;
	if (f == 0)
	{
		ft_printf("Error: no sprites found for direction '%s'\n",
			dir_name(d));
		exit(1);
	}
}

void	load_player_sprites(t_game *game)
{
	int	d;

	d = 0;
	while (d < DIR_COUNT)
	{
		load_direction_sprites(game, d);
		d++;
	}
}
