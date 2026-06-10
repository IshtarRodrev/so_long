/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:14:27 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/14 19:39:54 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static unsigned long	count(const char *str, const char *set,
		unsigned long index, int dir)
{
	while (ft_strchr(set, str[index]) != NULL && str[index] != '\0')
	{
		if (dir == -1 && index == 0)
			return (0);
		index += dir;
	}
	return (index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			slen;
	unsigned long	start;
	unsigned long	end;

	if (s1 == NULL)
		return (NULL);
	if (*s1 == '\0' || set == NULL)
		return (ft_strdup(s1));
	slen = ft_strlen(s1);
	start = count(s1, set, 0, 1);
	end = count(s1, set, slen - 1, -1) + 1;
	if (end < start)
		return (ft_calloc(1, 1));
	return (ft_substr(s1, start, end - start));
}
/*	Allocates memory (using malloc(3)) and returns a copy of ’s1’ with 
	characters from ’set’ removed from the beginning and the end.*/
/*	Returns the trimmed string. NULL if the allocation fails.*/
/*	#include <stdio.h>

	int	main(void)
	{
		char const		*src = " hi ";
		char const		*set = " ih";
		char			*strtrim;

		strtrim = ft_strtrim(src, set);
		printf(">%s<\n", strtrim);
		return (0);
	}*/