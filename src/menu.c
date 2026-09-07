#include "libft.h"
#include "so_long.h"
#include <dirent.h>
#include <stdlib.h>

# define MAPS_DIR "maps"

/******************************************************************************/
/*								MAP LIST SCAN								  */
/******************************************************************************/

static char	*build_map_path(const char *fname)
{
	return (ft_strjoin(MAPS_DIR "/", fname));
}

static int	add_map_name(const char *fname)
{
	char	*path;

	path = build_map_path(fname);
	if (!path)
		return (0);
	g_game.map_names[g_game.map_count++] = path;
	return (1);
}

static int	scan_maps_dir(void)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(MAPS_DIR);
	if (!dir)
		return (0);
	g_game.map_count = 0;
	entry = readdir(dir);
	while (entry && g_game.map_count < MENU_MAX_MAPS)
	{
		if (has_valid_extension(entry->d_name) && !add_map_name(entry->d_name))
		{
			closedir(dir);
			return (0);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (g_game.map_count > 0);
}

/******************************************************************************/
/*								MENU RENDERING								  */
/******************************************************************************/

static char	*build_entry_label(int index)
{
	char	*num;
	char	*tmp;
	char	*label;

	num = ft_itoa(index + 1);
	if (!num)
		return (NULL);
	tmp = ft_strjoin(num, " ");
	free(num);
	if (!tmp)
		return (NULL);
	label = ft_strjoin(tmp, g_game.map_names[index]);
	free(tmp);
	return (label);
}

static void	draw_map_list(void)
{
	int		i;
	char	*label;

	g_game.menu_imgs[g_game.menu_img_count++] = mlx_put_string(g_game.mlx,
			"so_long - choose a map (press 1-9, ESC to quit):", 40, 40);
	i = 0;
	while (i < g_game.map_count)
	{
		label = build_entry_label(i);
		if (label)
		{
			g_game.menu_imgs[g_game.menu_img_count++] =
				mlx_put_string(g_game.mlx, label, 40, 80 + i * 30);
			free(label);
		}
		i++;
	}
}

static void	show_status(const char *msg)
{
	if (g_game.status_img)
	{
		mlx_delete_image(g_game.mlx, g_game.status_img);
		g_game.status_img = NULL;
	}
	g_game.status_img = mlx_put_string(g_game.mlx, msg, 40,
			80 + g_game.map_count * 30 + 30);
}

/******************************************************************************/
/*								   TRANSITION								  */
/******************************************************************************/

static void	clear_menu_images(void)
{
	int	i;

	i = 0;
	while (i < g_game.menu_img_count)
	{
		mlx_delete_image(g_game.mlx, g_game.menu_imgs[i]);
		i++;
	}
	g_game.menu_img_count = 0;
	if (g_game.status_img)
	{
		mlx_delete_image(g_game.mlx, g_game.status_img);
		g_game.status_img = NULL;
	}
}

static void	free_map_names(void)
{
	int	i;

	i = 0;
	while (i < g_game.map_count)
	{
		free(g_game.map_names[i]);
		i++;
	}
	g_game.map_count = 0;
}

static void	start_game(char **map)
{
	clear_menu_images();
	free_map_names();
	g_game.map = map;
	init_camera();
	mlx_set_window_size(g_game.mlx, g_game.view_cols * TILE_SIZE,
			g_game.view_rows * TILE_SIZE);
	mlx_resize_image(g_game.img, g_game.view_cols * TILE_SIZE,
			g_game.view_rows * TILE_SIZE);
	render_map();
	mlx_key_hook(g_game.mlx, key_hook, NULL);
}

/******************************************************************************/
/*								MENU KEY HOOK								  */
/******************************************************************************/

static int	key_to_index(mlx_key_data_t keydata)
{
	if (keydata.key >= MLX_KEY_1 && keydata.key <= MLX_KEY_9)
		return (keydata.key - MLX_KEY_1);
	return (-1);
}

static void	try_select_map(int index)
{
	t_lay	lay;
	char	**map;

	map = load_and_validate(g_game.map_names[index], &lay);
	if (!map)
	{
		show_status("Error: that map failed validation (see terminal) - pick another");
		return ;
	}
	start_game(map);
}

static void	menu_key_hook(mlx_key_data_t keydata, void *param)
{
	int	index;

	(void)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	index = key_to_index(keydata);
	if (index >= 0 && index < g_game.map_count)
		try_select_map(index);
}

/******************************************************************************/
/*								 PUBLIC ENTRY								  */
/******************************************************************************/

void	start_map_menu(void)
{
	if (!scan_maps_dir())
	{
		ft_printf("Error: no '.ber' maps found in '%s'\n", MAPS_DIR);
		exit(1);
	}
	draw_map_list();
	mlx_key_hook(g_game.mlx, menu_key_hook, NULL);
}
