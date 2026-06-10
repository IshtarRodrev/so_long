/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:00:50 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/15 17:47:19 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_start;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_start = dst;
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		n--;
	}
	return (dst_start);
}
/*The memcpy() function copies n bytes from memory area src to memory area dst.
	If dst and src overlap, behavior is undefined.  Applications in which dst and
	src might overlap should use memmove(3) instead.*/
/*The memcpy() function returns the original value of dst.*/