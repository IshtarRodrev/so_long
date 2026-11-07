/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:42:55 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 20:33:49 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static mlx_texture_t	*load_required_texture(t_game *game, const char *path)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (!tex)
	{
		print_error("failed to load sprite", path);
		exit_game(game, 1);
	}
	return (tex);
}

static mlx_texture_t	*load_named(const char *name, const char *direction)
{
	char	path[128];

	ft_strlcpy(path, SPRITE_DIR "/", sizeof(path));
	ft_strlcat(path, name, sizeof(path));
	ft_strlcat(path, direction, sizeof(path));
	return (mlx_load_png(path));
}

/* Loads <name>/down.png, <name>/up.png, <name>/left.png and <name>/right.png
** from SPRITE_DIR. */

static void	load_faces(mlx_texture_t **tex, const char *name)
{
	tex[DIR_DOWN] = load_named(name, "/down.png");
	tex[DIR_UP] = load_named(name, "/up.png");
	tex[DIR_LEFT] = load_named(name, "/left.png");
	tex[DIR_RIGHT] = load_named(name, "/right.png");
}

static void	load_required_faces(t_game *game, mlx_texture_t **tex,
		const char *name)
{
	int	face;

	load_faces(tex, name);
	face = 0;
	while (face < DIR_COUNT)
	{
		if (!tex[face])
		{
			print_error("failed to load the sprites of", name);
			exit_game(game, 1);
		}
		face++;
	}
}

void	load_pattern_sprites(t_game *game)
{
	load_required_faces(game, game->desk_tex, "desk");
	load_required_faces(game, game->table_tex, "table");
	game->broken_sign_tex = load_required_texture(game,
			BROKEN_SIGN_SPRITE_PATH);
	game->facing_wall_tex = mlx_load_png(WALL_DOWN_SPRITE_PATH);
	load_glass_sprites(game);
	game->flowerpot_tex = mlx_load_png(FLOWERPOT_SPRITE_PATH);
	game->asphalt_tex = mlx_load_png(ASPHALT_SPRITE_PATH);
	game->grass_tex = mlx_load_png(GRASS_SPRITE_PATH);
	game->tree_tex = mlx_load_png(TREE_SPRITE_PATH);
	game->shower_tex[DIR_RIGHT] = mlx_load_png(SHOWER_RIGHT_SPRITE_PATH);
	game->shower_tex[DIR_LEFT] = mlx_load_png(SHOWER_LEFT_SPRITE_PATH);
	load_faces(game->toilet_tex, "toilet");
	load_faces(game->lockers_tex, "lockers");
	load_faces(game->sink_tex, "sink");
	load_faces(game->kitchen_tex, "kitchen");
	load_faces(game->coffee_tex, "coffee");
	load_faces(game->water_cooler_tex, "water_cooler");
	load_faces(game->fridge_tex, "fridge");
	load_faces(game->vending_tex, "vending_machine");
}
