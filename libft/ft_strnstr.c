/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:14:44 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/28 14:20:22 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlen;

	needlen = ft_strlen(needle);
	if (needle == 0 || !*needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	if (*haystack == '\0')
		return (NULL);
	while (len >= needlen && *haystack)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, needlen) == 0)
		{
			return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
/*The strnstr() function locates the first occurrence of the null-terminated
	string needle in the string haystack, where not more than len characters are
	searched.  Characters that appear after a `\0' character are not searched.
	Since the strnstr() function is a FreeBSD specific API, it should only be
	used when portability is not a concern.*/
/*If needle is an empty string, haystack is returned; if needle occurs nowhere
	in haystack, NULL is returned; otherwise a pointer to the first	character
	of the first occurrence of needle is returned.*/
/*	res = strnstr((void *)0, "fake", 3);	<- segmentation fault case*/
/*	#include <stdio.h>
	#include <string.h>

	int	main(void)
	{
		const char	haystack[30]	= "aaabcabcd\0";
		const char	needle[20] 		= "aaabc";
		char		*res;

		res = strnstr(haystack, needle, 5);
		printf ("%s\n", res);
		res = ft_strnstr(haystack, needle, 5);
		printf ("%s\n", res);
		return (0);
	}
*/