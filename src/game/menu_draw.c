/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 17:47:04 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/*
** Shows a nearly black band over the lower 30 % of the window, then the menu
** picture 40 px from the left, top and bottom window borders, scaled to fit
** that height. Both are drawn first so the text stays on top.
*/
void	draw_menu_picture(t_game *game)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	uint32_t		w;

	img = color_image(game, RGBA_MENU_BAND, WINDOW_W, WINDOW_H * 3 / 10);
	game->scene.menu[MENU_LINES + 1] = img;
	if (mlx_image_to_window(game->mlx, img, 0, WINDOW_H - img->height) < 0)
		fail(game, "failed to create image");
	tex = load_required_texture(game, "menu", "rayan");
	img = mlx_texture_to_image(game->mlx, tex);
	game->scene.menu[MENU_LINES] = img;
	w = tex->width * (WINDOW_H - 80) / tex->height;
	mlx_delete_texture(tex);
	if (!img || !mlx_resize_image(img, w, WINDOW_H - 80)
		|| mlx_image_to_window(game->mlx, img, 40, 40) < 0)
		fail(game, "failed to create image");
}

/*
** Puts line i of the MENU_LINES text lines in the bottom right corner,
** right-aligned 40 px from the right border; the last line sits 40 px above
** the bottom border and every line above it 40 px higher (put_title then
** moves lines 0 and 1 to the top). False on failure.
*/
static bool	put_line(t_game *game, int i, const char *text)
{
	mlx_image_t	*img;

	img = mlx_put_string(game->mlx, text, 0, 0);
	if (!img)
		return (false);
	game->scene.menu[i] = img;
	img->instances[0].x = WINDOW_W - 40 - (int) img->width;
	img->instances[0].y = WINDOW_H - 40 - (int) img->height
		- (MENU_LINES - 1 - i) * 40;
	return (true);
}

/*
** Puts "SO_LONG", teal and scaled MENU_TITLE_SCALE times, in the top right
** corner 40 px from the top and the right border, and the subtitle aligned
** 20 px below it. False on failure.
*/
static bool	put_title(t_game *game)
{
	mlx_image_t	*img;

	if (!put_line(game, 0, "./SO_LONG")
		|| !put_line(game, 1, "<42 Heilbronn cluster maintenance edition>"))
		return (false);
	img = game->scene.menu[0];
	tint_image(img, RGBA_MENU_TITLE);
	if (!mlx_resize_image(img, img->width * MENU_TITLE_SCALE,
			img->height * MENU_TITLE_SCALE))
		return (false);
	img->instances[0].x = WINDOW_W - 40 - (int) img->width;
	img->instances[0].y = 40;
	game->scene.menu[1]->instances[0].y = 40 + (int) img->height + 20;
	return (true);
}

/*
** Makes the map name and "Get ready!" fuchsia, scales them MENU_TEXT_SCALE
** times and moves them MENU_SHIFT_Y px up and MENU_SHIFT_X px left of the
** bottom text block, still right-aligned, "Get ready!" 20 px below the map
** name.
*/
static bool	place_info(t_game *game)
{
	mlx_image_t	*img;
	int			y;
	int			i;

	y = game->scene.menu[2]->instances[0].y - MENU_SHIFT_Y;
	i = 2;
	while (i <= 3)
	{
		img = game->scene.menu[i];
		tint_image(img, RGBA_MENU_INFO);
		if (!mlx_resize_image(img, img->width * MENU_TEXT_SCALE,
				img->height * MENU_TEXT_SCALE))
			return (false);
		img->instances[0].x = WINDOW_W - 40 - MENU_SHIFT_X - (int) img->width;
		img->instances[0].y = y;
		y += (int) img->height + 20;
		i++;
	}
	return (true);
}

/*
** Shows the title, the map name (no directories, no .ber), "Get ready!"
** and the controls (yellow).
*/
void	draw_menu_text(t_game *game, const char *map_name)
{
	char	*label;
	bool	ok;

	if (ft_strrchr(map_name, '/'))
		map_name = ft_strrchr(map_name, '/') + 1;
	label = ft_strjoin("> map: ", map_name);
	if (!label)
		fail(game, "memory allocation failed");
	label[ft_strlen(label) - 4] = '\0';
	ok = put_line(game, 2, label);
	free(label);
	if (!ok || !put_title(game)
		|| !put_line(game, 3, "Get ready!")
		|| !put_line(game, 4, "Press any key to start or ESC to exit"))
		fail(game, "failed to create image");
	tint_image(game->scene.menu[4], RGBA_MENU_PRESS);
	if (!place_info(game))
		fail(game, "failed to create image");
}
