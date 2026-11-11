/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:00:00 by akechedz          #+#    #+#             */
/*   Updated: 2026/11/07 12:00:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

/* Prints "Error\n<msg>[ '<detail>']\n" to stderr. detail may be NULL. */
void	print_error(const char *msg, const char *detail)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *) msg, 2);
	if (detail)
	{
		ft_putstr_fd(" '", 2);
		ft_putstr_fd((char *) detail, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}

/* Prints "Error\n<msg>\n" to stderr. Always returns 0. */
int	map_error(const char *msg)
{
	print_error(msg, NULL);
	return (0);
}

/* Prints "Error\n<msg>\n", frees everything and ends the program with 1. */
void	fail(t_game *game, const char *msg)
{
	print_error(msg, NULL);
	exit_game(game, 1);
}
