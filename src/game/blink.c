/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:49:21 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Blinks "Get ready!" and the "Press any key" line together: MENU_BLINK_SEC
** seconds shown, then as long hidden. MLX42 cannot remove loop hooks, so
** once the game has started and the menu images are gone, this does nothing.
*/
void	menu_blink_hook(void *param)
{
	t_game	*game;
	bool	on;

	game = param;
	if (!game->scene.menu[3] || !game->scene.menu[4])
		return ;
	on = (int)(mlx_get_time() / MENU_BLINK_SEC) % 2 == 0;
	game->scene.menu[3]->enabled = on;
	game->scene.menu[4]->enabled = on;
}

/*
** Blinks every broken sign on the map: SIGN_BLINK_SEC seconds shown, then as
** long hidden. It switches the shared sign image, so the signs of collected
** tasks, whose own instances are hidden, stay hidden.
*/
void	sign_blink_hook(void *param)
{
	t_game		*game;
	mlx_image_t	*sign;

	game = param;
	sign = cached_image(game, game->textures.broken_sign);
	sign->enabled = (int)(mlx_get_time() / SIGN_BLINK_SEC) % 2 == 0;
}
