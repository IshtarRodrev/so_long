/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:12:02 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/18 19:31:53 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s) + 1;
	while (len > 0)
	{
		len--;
		if (*(s + len) == (unsigned char)c)
		{
			return ((char *)(s + len));
		}
	}
	return (NULL);
}
/*The strchr() function locates the first occurrence of c (converted to a
     char) in the string pointed to by s.  The terminating null character is
     considered to be part of the string; therefore if c is `\0', the func-
     tions locate the terminating `\0'.

     The strrchr() function is identical to strchr(), except it locates the
     last occurrence of c.*/
/*The functions strchr() and strrchr() return a pointer to the located
     character, or NULL if the character does not appear in the string.*/
/*	#include "libft.h"
	#include <stdio.h>
	#include <string.h>

	int	main(void)
	{
		const char	dest[30] = "bonjour";
		char		*res;

		res = ft_strrchr(dest + 2, 's');
		printf ("%s\n", res);
		return (0);
	}
*/