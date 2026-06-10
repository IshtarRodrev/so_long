/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:33:04 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/14 15:30:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}
/*	The strchr() function locates the first occurrence of c (converted to a
	char) in the string pointed to by s.  The terminating null character is
	considered to be part of the string; therefore if c is `\0', the func-
	tions locate the terminating `\0'.*/ 