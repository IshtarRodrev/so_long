/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:28:21 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/02 16:55:38 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	long	diff;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	diff = slen - start;
	if (diff <= 0)
		return (ft_calloc(1, 1));
	if (len > (unsigned long) diff)
		len = diff;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
/*	Allocates memory using malloc(3) and returns a substring from the string ’s’
	The substring starts at index ’start’ and has a maximum length of ’len’*/