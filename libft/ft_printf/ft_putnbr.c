/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:47:06 by akechedz          #+#    #+#             */
/*   Updated: 2026/01/29 20:20:56 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_sym(long n)
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

static void	get_chars(long n, char *result, size_t len)
{
	result[len] = '\0';
	while (n > 0)
	{
		result[--len] = (n % 10) + '0';
		n /= 10;
	}
}

int	ft_putnbr(int n)
{
	char	c[12];
	long	num;
	size_t	len;
	int		neg;

	num = (long)n;
	neg = 0;
	if (num < 0)
	{
		neg = 1;
		num = -num;
	}
	len = count_sym(num) + neg;
	if (neg == 1)
		c[0] = '-';
	get_chars(num, c, len);
	if (n == 0)
		c[0] = '0';
	return (write(1, c, len));
}
