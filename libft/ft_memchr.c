/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:35:45 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/18 17:07:08 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;

	str = s;
	while (n > 0)
	{
		if (*str == (unsigned char)c)
		{
			return ((void *)str);
		}
		str++;
		n--;
	}
	return (NULL);
}
/*The memchr() function locates the first occurrence of c (converted to an
	unsigned char) in string s.*/
/*The memchr() function returns a pointer to the byte located, or NULL if no
	such byte exists within n bytes.*/
/*	#include <stdio.h>
	#include <string.h>

	int	main(void)
	{
		const char	str1[30] = "bonjour";
		const char	str2[20] = "abcdwxyz\0";
		void		*res;

		res = ft_memchr(str1, 'b', 4);
		printf ("%s\n", res);
		res = memchr(str1, 'b', 4);
		printf ("%s\n", res);
		return (0);
	}
*/