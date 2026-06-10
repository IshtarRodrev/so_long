/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:06:51 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/16 19:47:12 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_start;

	dst_start = dst;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	while (dst > src && len > 0)
	{
		len--;
		*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
	}
	while (len > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		len--;
	}
	return (dst_start);
}
/*The memmove() function copies len bytes from string src to string dst.
	The two strings may overlap; the copy is always done in a 
	non-destructive manner.*/
/*The memmove() function returns the original value of dst.*/
/* 
#include "libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	dest[30] = "0123456789";
	char	*srcs = "====";
	char	*result_str;
	char	r_dest[30] = "0123456789";
	char	*r_result_str;

	result_str = memmove((void *)dest, (const void *)dest + 2, 4);
	r_result_str = ft_memmove((void *)r_dest, (const void *)r_dest + 2, 4);
	printf("expectation:	%s\nreality:	%s\n", result_str, r_result_str);
} */