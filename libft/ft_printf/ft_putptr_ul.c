/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_ul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:56:58 by akechedz          #+#    #+#             */
/*   Updated: 2025/12/09 21:05:47 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_hex_digits_ul(unsigned long n)
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

static void	get_hex_chars_ul(unsigned long n, char *result, size_t len)
{
	char	*base;

	base = "0123456789abcdef";
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = base[n % 16];
		n /= 16;
	}
}

int	ft_putptr_ul(unsigned long ptr)
{
	size_t	len;
	char	buff[17];

	if (ptr == 0)
		return (write(1, PTRNULL, NPTRSIZE));
	if (write(1, "0x", 2) == -1)
		return (-1);
	len = count_hex_digits_ul(ptr);
	get_hex_chars_ul(ptr, buff, len);
	if (write(1, buff, len) == -1)
		return (-1);
	return ((int)(len + 2));
}
