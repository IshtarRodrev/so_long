/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:53:11 by akechedz          #+#    #+#             */
/*   Updated: 2026/05/06 18:49:44 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_hex_digits(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static void	get_hex_chars(unsigned int n, char *result, size_t len, int cs)
{
	char	*base;

	if (cs)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = base[n % 16];
		n /= 16;
	}
}

int	ft_puthex_unsigned(unsigned int n, int uppercase)
{
	size_t	len;
	char	buff[9];

	len = count_hex_digits(n);
	get_hex_chars(n, buff, len, uppercase);
	return (write(1, buff, len));
}
