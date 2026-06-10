/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:26:43 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/18 19:12:28 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	if (n == 0)
	{
		return (0);
	}
	while (*str1 == *str2 && n > 1)
	{
		str1++;
		str2++;
		n--;
	}
	return ((unsigned char) *str1 - (unsigned char) *str2);
}
/*The memcmp() function compares byte string s1 against byte string s2.  
	Both strings are assumed to be n bytes long.*/
/*The memcmp() function returns zero if the two strings are identical, 
	otherwise returns the difference between the first two differing bytes 
	(treated as unsigned char values, so that `\200' is greater than `\0', for 
	example).  Zero-length strings are always identical.  This behavior is not 
	required by C and portable code should only depend on the sign of the 
	returned value.*/
/*	#include <stdio.h>
	#include <string.h>

	int	main(void)
	{
		const char	str1[30] = "abcdefghij";
		const char	str2[20] = "abcdefgxyz\0";
		int			res;

		res = ft_memcmp((const void *)str1, (const void *)str2, 7);
		printf ("%d\n", res);
		res = memcmp((const void *)str1, (const void *)str2, 7);
		printf ("%d\n", res);
		return (0);
	}
*/