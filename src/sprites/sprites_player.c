/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:48:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:12 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "so_long.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static const char	*dir_name(int d)
{
	if (d == DIR_UP)
		return ("back");
	if (d == DIR_LEFT)
		return ("left");
	if (d == DIR_RIGHT)
		return ("right");
	return ("front");
}

static char	*sprite_path(const char *dir_name, int frame)
{
	char	buf[128];
	char	num[3];

	num[0] = '0' + frame / 10 % 10;
	num[1] = '0' + frame % 10;
	num[2] = '\0';
	ft_strlcpy(buf, SPRITE_DIR "/player/", sizeof(buf));
	ft_strlcat(buf, dir_name, sizeof(buf));
	ft_strlcat(buf, "/", sizeof(buf));
	ft_strlcat(buf, num, sizeof(buf));
	ft_strlcat(buf, ".png", sizeof(buf));
	return (ft_strdup(buf));
}

/* Loads frame f of direction d. Returns false if its file does not exist. */
static bool	load_frame(t_game *game, int d, int f)
{
	char	*path;
	int		fd;

	path = sprite_path(dir_name(d), f + 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (false);
	}
	close(fd);
	game->player_tex[d][f] = mlx_load_png(path);
	free(path);
	if (!game->player_tex[d][f])
		fail(game, "failed to load player sprite");
	return (true);
}

static void	load_direction_sprites(t_game *game, int d)
{
	int	f;

	f = 0;
	while (f < SPRITE_FRAMES && load_frame(game, d, f))
		f++;
	game->player_frame_count[d] = f;
	if (f == 0)
	{
		print_error("no sprites found for direction", dir_name(d));
		exit_game(game, 1);
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
