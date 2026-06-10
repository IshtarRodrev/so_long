/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:54 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/25 16:23:32 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while ((*s1 == *s2 && n-- > 1) && (*s1 && *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/*The strcmp() and strncmp() functions lexicographically compare 
	the null-terminated strings s1 and s2.

	The strncmp() function compares not more than n characters.  
	Because strncmp() is designed for comparing strings rather than	binary 
	data, characters that appear after a `\0' character are not compared.*/
/*The strncmp() function return an integer greater than, equal to, or less than 
	0, according as the string s1 is greater than, equal to, or less than the 
	string s2.  The comparison is done using unsigned characters, so that 
	`\200' is greater than `\0'.*/
/*	#include <stdio.h>
	#include <string.h>

	int	main(void)
	{
		const char	str1[30] = "zyxbcdefgh\200";
		const char	str2[20] = "abcdwxyz\0";
		int			res;

		res = ft_strncmp(str1, str2, 0);
		printf ("%d\n", res);
		res = strncmp(str1, str2, 0);
		printf ("%d\n", res);
		return (0);
	}
*/