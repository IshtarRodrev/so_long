/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:11:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 19:45:38 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

#include <stdlib.h>

static void	update_player_dir(t_game *game, int dx, int dy)
{
	if (dy < 0)
		game->player_dir = DIR_BACK;
	else if (dy > 0)
		game->player_dir = DIR_FRONT;
	else if (dx < 0)
		game->player_dir = DIR_LEFT;
	else if (dx > 0)
		game->player_dir = DIR_RIGHT;
}

int	move_player(t_game *game, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = game->progress.player.x + dx;
	ny = game->progress.player.y + dy;
	update_player_dir(game, dx, dy);
	if (ny < 0 || ny >= game->rows || nx < 0 || nx >= game->cols
		|| game->map[ny][nx] == '1' || is_collected(game, nx, ny)
		|| (game->map[ny][nx] == 'E'
			&& game->progress.collectibles_left > 0))
		return (render_map(game), 0);
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
	if (game->map[ny][nx] == 'E')
	{
		ft_printf("You won!\n");
		exit(0);
	}
	game->progress.player = (t_point){nx, ny};
	if (game->map[ny][nx] == 'C')
		collect_tile(game, nx, ny);
	game->player_frame++;
	return (render_map(game), 0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		move_player(game, 0, -1);
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		move_player(game, 0, 1);
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		move_player(game, -1, 0);
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		move_player(game, 1, 0);
}
