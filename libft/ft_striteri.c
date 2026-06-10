/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:16:45 by akechedz          #+#    #+#             */
/*   Updated: 2025/08/10 18:55:50 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	while (len-- > 0)
	{
		f(len, &s[len]);
	}
	return ;
}

/*	Applies the function ’f’ to each character of the string passed as argument,
	passing its index as the first argument. Each character is passed by address
	to ’f’ so it can be modified if necessary.*/
/*	Return value: none*/