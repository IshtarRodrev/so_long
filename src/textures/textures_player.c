/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:48:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:12 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <fcntl.h>
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

/* Writes the path of frame number frame (1, 2, ...) of direction d. */
static void	frame_path(char *path, size_t size, int d, int frame)
{
	char	file[32];
	char	num[3];

	num[0] = '0' + frame / 10 % 10;
	num[1] = '0' + frame % 10;
	num[2] = '\0';
	ft_strlcpy(file, dir_name(d), sizeof(file));
	ft_strlcat(file, "/", sizeof(file));
	ft_strlcat(file, num, sizeof(file));
	texture_path(path, size, "player", file);
}

/* Loads frame f of direction d. Returns false if its file does not exist. */
static bool	load_frame(t_game *game, int d, int f)
{
	char	path[128];
	int		fd;

	frame_path(path, sizeof(path), d, f + 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	game->textures.player[d][f] = mlx_load_png(path);
	if (!game->textures.player[d][f])
		fail(game, "failed to load player sprite");
	return (true);
}

static void	load_direction_textures(t_game *game, int d)
{
	int	f;

	f = 0;
	while (f < SPRITE_FRAMES && load_frame(game, d, f))
		f++;
	game->textures.player_frames[d] = f;
	if (f == 0)
	{
		print_error("no sprites found for direction", dir_name(d));
		exit_game(game, 1);
	}
}

void	load_player_textures(t_game *game)
{
	int	d;

	d = 0;
	while (d < DIR_COUNT)
	{
		load_direction_textures(game, d);
		d++;
	}
}
