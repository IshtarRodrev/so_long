/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akechedz <akechedz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:42:48 by akechedz          #+#    #+#             */
/*   Updated: 2026/05/15 17:53:41 by akechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	len;

	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	return (write(1, s, len));
}

int	swtch_fmt(const char *fmt, va_list list)
{
	if (*fmt == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (*fmt == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (*fmt == 'p')
		return (ft_putptr_ul((unsigned long) va_arg(list, void *)));
	else if (*fmt == 'd' || *fmt == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (*fmt == 'u')
		return (ft_putnbr_unsigned(va_arg(list, unsigned int)));
	else if (*fmt == 'x')
		return (ft_puthex_unsigned(va_arg(list, unsigned int), 0));
	else if (*fmt == 'X')
		return (ft_puthex_unsigned(va_arg(list, unsigned int), 1));
	else if (*fmt == '%')
		return (ft_putchar(*fmt));
	else
	{
		if (write(1, fmt - 1, 2) == -1)
			return (-1);
		return (2);
	}
}

int	ft_print_intern(va_list	arg, const char *fmt)
{
	int	count;
	int	tmp;

	count = 0;
	tmp = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			if (write(1, fmt, 1) == -1)
				return (-1);
			count++;
		}
		else
		{
			if (*(fmt + 1) == '\0')
				return (-1);
			tmp = swtch_fmt(++fmt, arg);
			if (tmp == -1)
				return (-1);
			count += tmp;
		}
		fmt++;
	}
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	arg;
	int		count;

	count = 0;
	if (fmt == NULL)
		return (-1);
	va_start(arg, fmt);
	count = ft_print_intern(arg, fmt);
	va_end(arg);
	return (count);
}
