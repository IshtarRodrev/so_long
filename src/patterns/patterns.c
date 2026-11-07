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

/* Loads <name>_down.png, <name>_up.png,
<name>_left.png and <name>_right.png. */

static void	load_faces(mlx_texture_t **tex, const char *name)
{
	tex[FACE_DOWN] = load_named(name, "_down.png");
	tex[FACE_UP] = load_named(name, "_up.png");
	tex[FACE_LEFT] = load_named(name, "_left.png");
	tex[FACE_RIGHT] = load_named(name, "_right.png");
}

static void	load_required_faces(t_game *game, mlx_texture_t **tex,
		const char *name)
{
	int	face;

	load_faces(tex, name);
	face = 0;
	while (face < FACE_COUNT)
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
	game->glass_down_right_tex = mlx_load_png(GLASS_DR_SPRITE_PATH);
	game->glass_down_left_tex = mlx_load_png(GLASS_DL_SPRITE_PATH);
	game->shower_tex[FACE_RIGHT] = mlx_load_png(SHOWER_RIGHT_SPRITE_PATH);
	game->shower_tex[FACE_LEFT] = mlx_load_png(SHOWER_LEFT_SPRITE_PATH);
	load_faces(game->toilet_tex, "toilet");
	load_faces(game->lockers_tex, "lockers");
	load_faces(game->sink_tex, "sink");
	load_faces(game->kitchen_tex, "kitchen");
	load_faces(game->coffee_tex, "coffee");
	load_faces(game->water_cooler_tex, "water_cooler");
	load_faces(game->fridge_tex, "fridge");
	load_faces(game->vending_tex, "vending_machine");
}
