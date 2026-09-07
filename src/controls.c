#include "libft.h"
#include "so_long.h"
#include <stdlib.h>

/******************************************************************************/
/*								WINDOW SETUP								  */
/******************************************************************************/

static int	setup_window(void)
{
	g_game.mlx = mlx_init(MENU_WIN_W, MENU_WIN_H, "so_long", false);
	if (!g_game.mlx)
		return (0);
	g_game.img = mlx_new_image(g_game.mlx, MENU_WIN_W, MENU_WIN_H);
	if (!g_game.img || mlx_image_to_window(g_game.mlx, g_game.img, 0, 0) < 0)
		return (0);
	return (1);
}

void	init_game(void)
{
	if (!setup_window())
	{
		ft_printf("Error: failed to initialize window\n");
		exit(1);
	}
	load_player_sprites();
	start_map_menu();
	mlx_loop(g_game.mlx);
}
