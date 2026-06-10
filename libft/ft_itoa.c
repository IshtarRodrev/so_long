/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:59 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/14 10:21:28 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_sym(long n)
{
	size_t	len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*get_chars(long n, char	*result, size_t len)
{
	result[len] = '\0';
	while (n > 0)
	{
		result[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;
	int		neg;
	long	num;

	num = (long) n;
	if (n == 0)
		return (ft_strdup("0"));
	neg = 0;
	if (num < 0)
	{
		neg = 1;
		num *= -1;
	}
	len = count_sym(num) + neg;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (neg == 1)
	{
		*result = '-';
	}
	result = get_chars(num, result, len);
	return (result);
}
/*	Allocates memory (using malloc(3)) and returns a string representing the 
	integer received as an argument. Negative numbers must be handled.*/
/*	Returns the string representing the integer. NULL if the allocation fails.*/
/*	// n -= (n * 2) // n = -n*/
/*	#include <stdio.h>

	int	main(void)
	{
		int		n;
		char	*dest;

		n = -12345678;
		dest = ft_itoa(n);
		printf(dest);
		return (0);
	}
*/