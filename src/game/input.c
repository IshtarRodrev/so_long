/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:11:30 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 19:45:38 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	update_player_dir(t_game *game, int dx, int dy)
{
	if (dy < 0)
		game->player_dir = DIR_UP;
	else if (dy > 0)
		game->player_dir = DIR_DOWN;
	else if (dx < 0)
		game->player_dir = DIR_LEFT;
	else if (dx > 0)
		game->player_dir = DIR_RIGHT;
}

/* True if the player may step onto (x, y): not a wall, not a locked exit. */
static bool	can_enter(t_game *game, int x, int y)
{
	if (!in_map(game, x, y) || game->map[y][x] == '1')
		return (false);
	return (game->map[y][x] != 'E' || game->progress.collectibles_left == 0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = game->progress.player.x + dx;
	ny = game->progress.player.y + dy;
	update_player_dir(game, dx, dy);
	if (!can_enter(game, nx, ny))
	{
		render_map(game);
		return ;
	}
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
	if (game->map[ny][nx] == 'E')
	{
		ft_printf("You won!\n");
		mlx_close_window(game->mlx);
		return ;
	}
	game->progress.player = (t_point){nx, ny};
	if (game->map[ny][nx] == 'C' && !is_collected(game, nx, ny))
		collect_tile(game, nx, ny);
	game->player_frame++;
	render_map(game);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		move_player(game, 0, -1);
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		move_player(game, 0, 1);
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		move_player(game, -1, 0);
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		move_player(game, 1, 0);
}
