/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:23:43 by akechedz          #+#    #+#             */
/*   Updated: 2025/10/16 10:18:36 by akechedz         ###   ########.fr       */
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	str = malloc(slen1 + slen2 + 1);
	if (str == NULL)
	/*
	size_t	slen1;
	size_t	slen2;
	size_t	buffer;
	// size_t	resulting_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	str = malloc(slen1 + slen2 + 1);
	if (str == NULL)
	{
		free(str);
		return (NULL);
	}
	buffer = slen1 + slen2 + 1;
	// resulting_len = slen1 + slen2;
	if (buffer <= resulting_len)
		return (NULL);
	str += slen1;
	buffer -= slen1;
	while (*s1 != '\0' && buffer > 1)
	{
		*str++ = *s1++;
		slen1++;
		buffer--;
	}
	return (str); */
		return (NULL);
	ft_strlcpy(str, s1, slen1 + 1);
	ft_strlcat(str, s2, slen1 + slen2 + 1);
	return (str);
}

/*	The strchr() function locates the first occurrence of c (converted to a
	char) in the string pointed to by s.  The terminating null character is
	considered to be part of the string; therefore if c is `\0', the func-
	tions locate the terminating `\0'.*/
/*	ft_strjoin
	Allocates memory (using malloc(3)) and returns a new string, which is the 
	result of concatenating ’s1’ and ’s2’.*/
/*	Returns the new string. NULL if the allocation fails.*/

/*memset
memmove*/