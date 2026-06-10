/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:55:28 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/10 14:27:11 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	word_count(char const *s, char c)
{
	int		words;
	char	*str;

	words = 0;
	str = (char *)s;
	while (str != NULL && *str != '\0')
	{
		if (*str == c)
		{
			str++;
			continue ;
		}
		str = ft_strchr(str, c);
		words++;
	}
	return (words);
}

static void	free_all(char **arr, int i)
{
	while (i >= 0)
		free(arr[i--]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**dest;
	char	*start;

	if (s == NULL)
		return (NULL);
	dest = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (*s++ == c)
			continue ;
		start = (char *)(--s);
		while (*s != c && *s != '\0')
			s++;
		dest[i] = ft_substr(start, 0, s - start);
		if (!dest[i++])
			return (free_all(dest, i - 2), NULL);
	}
	dest[i] = NULL;
	return (dest);
}
/*	Allocates memory (using malloc(3)) and returns an array of strings obtained 
	by splitting ’s’ using the character ’c’ as a delimiter. The array must end 
	with a NULL pointer.*/
/*	Returns the array of new strings resulting from the split. NULL if the 
	allocation fails.*/
/*	The free() function deallocates the memory allocation pointed to by ptr. If 
	ptr is a NULL pointer, no operation is performed.*/
/*	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	int	main(void)
	{
		char const	*s = "3.14159265358979323846264338327950288419716939937510";
		char const	c = '3';	
		char		**split_arr;
		// char const	*s = "_one_two_three";
		// char 		c = '_';
		split_arr = ft_split(s, c);
		while (*split_arr != NULL)
		{
			printf("%s\n", *split_arr++);
		}
		return (0);
	}
*/
/* 	char *tmp[3];
	char *hel = malloc(30);
	hel[0] = 'A';
	hel[1] = '\0';
	hel[9] = 'B';
	hel[10] = '\0';
	hel[19] = 'c';
	hel[29] = '\0';
	tmp[0] = hel;
	tmp[1] = &hel[9];
	tmp[2] = &hel[19]; 
	free(tmp[1]);
	printf("%s", tmp[2]); */