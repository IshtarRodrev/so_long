/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:52:26 by akechedz          #+#    #+#             */
/*   Updated: 2025/07/06 20:12:14 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int sym)
{
	if ((sym >= '\t' && sym <= '\r') || sym == ' ' )
	{
		return (sym);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	result;

	neg = 0;
	result = 0;
	while (ft_isspace(*str))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - 48);
		str++;
	}
	if (neg == 1)
		result *= -1;
	return (result);
}
