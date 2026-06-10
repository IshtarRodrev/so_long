/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:20:43 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/02 16:03:28 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	srcsize;

	srcsize = 0;
	while (*src != '\0')
	{
		if (dstsize > 1)
		{
			*dest = *src;
			dest++;
			dstsize--;
		}
		src++;
		srcsize++;
	}
	if (dstsize != 0)
		*dest = '\0';
	return (srcsize);
}
/*	The strlcpy() function copy strings with the same input	parameters and 
	output result as snprintf(3). It's designed to be safer, more 
	consistent, and less error prone replacement for the easily misused 
	function strncpy(3).*/
/*	strlcpy() takes the full size of the destination buffer and guarantee NUL-
	termination if there is room. Note that room for the NUL should be included 
	in dstsize.*/
/*	strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
	NUL-terminating the result if dstsize is not 0.*/
/*	If the src and dst strings overlap, the behavior is undefined.*/