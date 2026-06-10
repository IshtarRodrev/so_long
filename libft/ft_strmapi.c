/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:02:23 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/12 18:49:00 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*dest;

	if (s == NULL || f == NULL)
		return (NULL);
	index = 0;
	dest = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (*s != '\0')
	{
		dest[index] = f(index, *s);
		index++;
		s++;
	}
	dest[index] = '\0';
	return (dest);
}
/*	Applies the function f to each character of the string s, passing it's index
    as the first argumentand the character itself as the second. A newstring is 
    created (using malloc) to store the results from the successive applications 
	of f.*/
/*	Returns the string created from the successive applications of ’f’. 
	Returns NULL if the allocation fails.*/
/*	s: The string to iterate over. 
	f: The function to apply to each character. */