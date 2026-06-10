/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:58:06 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/14 19:47:16 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
/*  The calloc() function allocates memory for an array of nmemb elements of 
    size bytes each and returns a pointer to the allocated memory. The memory is 
    set to zero. If nmemb or size is 0, then calloc() returns either NULL, or a 
    unique pointer value that can later be successfully passed to free().*/
/*  If the multiplication of nmemb and size overflows, then calloc() returns
    NULL. If the allocation fails, then calloc() returns NULL and sets errno to
    ENOMEM. */
/*  Unless ptr is NULL, it must have been returned by an earlier call to 
    malloc(), calloc() or realloc(). If the area pointed to was moved, 
    a free(ptr) is done.*/
/*		void *malloc(size_t size);
	The malloc() function allocates size bytes of memory and returns a pointer 
	to the allocated memory.*/
/*	If successful, calloc(), malloc() functions return a pointer to allocated 
	emory. If there is an error, they return a NULL pointer and set errno to 
	ENOMEM.*/