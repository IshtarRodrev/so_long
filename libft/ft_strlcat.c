/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:02:39 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/02 17:09:17 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_size;
	size_t	dst_size;
	size_t	resulting_len;

	src_size = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (0);
	dst_size = ft_strlen(dst);
	resulting_len = src_size + dst_size;
	if (dstsize <= dst_size)
		return (dstsize + src_size);
	dst += dst_size;
	dstsize -= dst_size;
	while (*src != '\0' && dstsize > 1)
	{
		*dst++ = *src++;
		dst_size++;
		dstsize--;
	}
	if (dstsize > 0)
		*dst = '\0';
	return (resulting_len);
}
/*	strlcat() function concatenates strings with the same input parameters and 
	output result as snprintf(3). It's designed to be safer, more consistent, 
	and a less error prone replacement for the easily misused function strncat()

	strlcat() takes the full size of the destination buffer and guarantees
	NUL-termination if there is room. Note that room for the NUL should be
	included in dstsize.

	strlcat() appends string src to the end of dst. It will append at most 
	dstsize - strlen(dst) - 1 characters. It will then NUL-terminate, unless 
	dstsize is 0 or the original dst string was longer than dstsize (in practice
	this should not happen as it means that either dstsize is incorrect or that 
	dst is not a proper string).

	If the src and dst strings overlap, the behavior is undefined.*/
/* 	#include <stdio.h>
	#include <string.h>

	int	main(void)
	{
		char	dst[15] = "rrrrrr";
		char	*str;
		int		n;
		int		len;

		dst[11] = 'a';
		str = "lorem";
		n = 15;
		dst[11] = 'a';
		len = strlcat(dst, str, n);
		printf(">%s<, len=%d\n", dst, len);
		strcpy(dst, "rrrrrr");
		len = ft_strlcat(dst, str, n);
		printf(">%s<, len=%d\n", dst, len);
		return (0);
	}
*/
