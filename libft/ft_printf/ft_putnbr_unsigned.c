/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:39:04 by akechedz          #+#    #+#             */
/*   Updated: 2025/12/09 21:05:08 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits_unsigned(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	get_chars_unsigned(unsigned int n, char *result, size_t len)
{
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = (n % 10) + '0';
		n /= 10;
	}
}

int	ft_putnbr_unsigned(unsigned int n)
{
	size_t	len;
	char	buff[11];

	len = count_digits_unsigned(n);
	get_chars_unsigned(n, buff, len);
	return (write(1, buff, len));
}
