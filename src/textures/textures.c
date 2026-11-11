/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/* Writes SPRITE_DIR/<dir>/<file>.png into path (size bytes). */
void	texture_path(char *path, size_t size, const char *dir, const char *file)
{
	ft_strlcpy(path, SPRITE_DIR "/", size);
	ft_strlcat(path, dir, size);
	ft_strlcat(path, "/", size);
	ft_strlcat(path, file, size);
	ft_strlcat(path, ".png", size);
}

/* Loads SPRITE_DIR/<dir>/<file>.png; NULL if it is missing (optional). */
mlx_texture_t	*load_texture(const char *dir, const char *file)
{
	char	path[128];

	texture_path(path, sizeof(path), dir, file);
	return (mlx_load_png(path));
}

/* Like load_texture, but a missing file ends the game with an error. */
mlx_texture_t	*load_required_texture(t_game *game, const char *dir,
		const char *file)
{
	char			path[128];
	mlx_texture_t	*tex;

	texture_path(path, sizeof(path), dir, file);
	tex = mlx_load_png(path);
	if (!tex)
	{
		print_error("failed to load sprite", path);
		exit_game(game, 1);
	}
	return (tex);
}

/*
** Loads every sprite the game uses. Player, exit, broken sign, desks and
** tables are required; the rest is optional and simply not drawn if missing.
*/
void	load_textures(t_game *game)
{
	load_player_textures(game);
	game->textures.exit = load_required_texture(game, "exit", "tile");
	game->textures.broken_sign = load_required_texture(game, "broken_sign",
			"tile");
	game->textures.facing_wall = load_texture("wall", "down");
	game->textures.flowerpot = load_texture("flowerpot", "tile");
	game->textures.asphalt = load_texture("asphalt", "tile");
	game->textures.grass = load_texture("grass", "tile");
	game->textures.tree = load_texture("tree", "tile");
	game->textures.lamp = load_texture("lamp", "tile");
	game->textures.window = load_texture("window", "down");
	load_furniture_textures(game);
	load_glass_textures(game);
}
