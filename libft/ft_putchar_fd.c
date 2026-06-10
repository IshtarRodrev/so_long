/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:58:52 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/10 19:26:18 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
	return ;
}
/*	Outputs the character ’c’ to the specified file descriptor.*/
/*	Return value: none.*/
/*	In Unix type systems, a file descriptor (fd for short) is a small positive 
	integer used as reference to an open file in a process. */