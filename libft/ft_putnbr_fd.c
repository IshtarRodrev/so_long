/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:21:43 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/14 15:32:02 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static size_t	count_sym2(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	get_chars2(long n, char *result, size_t len)
{
	result[len] = '\0';
	while (n > 0)
	{
		result[--len] = (n % 10) + '0';
		n /= 10;
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c[12];
	long	num;
	size_t	len;
	int		neg;

	if (fd < 0)
		return ;
	num = (long) n;
	neg = 0;
	if (num < 0)
	{
		neg = 1;
		num *= -1;
	}
	len = count_sym2(num) + neg;
	if (neg == 1)
	{
		c[0] = '-';
	}
	get_chars2(num, c, len);
	if (n == 0)
		c[0] = '0';
	write(fd, c, len);
	return ;
}
/*	Outputs the integer ’n’ to the specified file descriptor.*/