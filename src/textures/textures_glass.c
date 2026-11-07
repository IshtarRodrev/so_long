/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_glass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/*
** Loads the 4 glass variants with one side drawn as <side> (dark or grass):
** down_right_<side>_left, down_right_<side>_right, down_left_<side>_left and
** down_left_<side>_right, in the order of the GLASS_DOWN_* indices.
*/
static void	load_glass_set(mlx_texture_t **set, const char *side)
{
	static const char	*fence[GLASS_SIDES] = {"down_right_", "down_right_",
		"down_left_", "down_left_"};
	static const char	*end[GLASS_SIDES] = {"_left", "_right", "_left",
		"_right"};
	char				name[64];
	int					i;

	i = 0;
	while (i < GLASS_SIDES)
	{
		ft_strlcpy(name, fence[i], sizeof(name));
		ft_strlcat(name, side, sizeof(name));
		ft_strlcat(name, end[i], sizeof(name));
		set[i] = load_texture("glass_fence", name);
		i++;
	}
}

/* Plain glass fence sprites and their dark and grass variants. */
void	load_glass_textures(t_game *game)
{
	game->textures.glass_down_right = load_texture("glass_fence", "down_right");
	game->textures.glass_down_left = load_texture("glass_fence", "down_left");
	load_glass_set(game->textures.glass_dark, "dark");
	load_glass_set(game->textures.glass_grass, "grass");
}

/* Deletes texture *tex if it was loaded and clears it. */
static void	delete_glass(mlx_texture_t **tex)
{
	if (*tex)
		mlx_delete_texture(*tex);
	*tex = NULL;
}

/* Deletes every glass fence sprite that was loaded. */
void	free_glass_textures(t_game *game)
{
	int	i;

	delete_glass(&game->textures.glass_down_right);
	delete_glass(&game->textures.glass_down_left);
	i = 0;
	while (i < GLASS_SIDES)
	{
		delete_glass(&game->textures.glass_dark[i]);
		delete_glass(&game->textures.glass_grass[i]);
		i++;
	}
}
