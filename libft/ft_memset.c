/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:52:41 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/15 14:30:25 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*value;

	value = ((unsigned char *)b);
	while (len > 0)
	{
		*value = (unsigned char)c;
		value++;
		len--;
	}
	return (b);
}
/* returns void of undefind type
fills the string with same single byte c 
*/
