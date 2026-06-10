/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:56:16 by akechedz          #+#    #+#             */
/*   Updated: 2025/10/06 06:03:09 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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
		return (NULL);
	ft_strlcpy(str, s1, slen1 + 1);
	ft_strlcat(str, s2, slen1 + slen2 + 1);
	return (str);
}
/*	Allocates memory (using malloc(3)) and returns a new string, which is the 
	result of concatenating ’s1’ and ’s2’.*/
/*	Returns the new string. NULL if the allocation fails.*/	