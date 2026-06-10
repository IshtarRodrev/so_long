/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:41:09 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/30 19:22:16 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	size;
	void	*s2;

	size = ft_strlen(s1) + 1;
	s2 = malloc(size);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, size);
	return (s2);
}
/*		void *malloc(size_t size);
	The malloc() function allocates size bytes of memory and returns a pointer 
	to the allocated memory.*/
/*	The strdup() function allocates sufficient memory for a copy of the string 
	s1, does the copy, and returns a pointer to it. 
	The pointer may subsequently be used as an argument to the function free(3).
If insufficient memory is available, NULL is returned and errno is set to ENOMEM
	*/