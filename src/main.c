/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 17:41:14 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/06 17:41:16 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("usage: ./so_long <map name>", NULL);
		return (1);
	}
	ft_bzero(&game, sizeof(game));
	init_game(&game, argv[1]);
	return (0);
}
