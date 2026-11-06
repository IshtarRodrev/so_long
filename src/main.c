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

	(void) argc;
	(void) argv;
	ft_bzero(&game, sizeof(game));
	init_game(&game);
	return (0);
}
