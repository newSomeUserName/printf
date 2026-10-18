/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_dispatch(char c, va_list *ap)
{
	if (c == 'c')
		return (ft_putchar_pf((char)va_arg(*ap, int)));
	if (c == 's')
		return (ft_putstr_pf(va_arg(*ap, char *)));
	if (c == 'p')
		return (ft_putptr_pf(va_arg(*ap, void *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_pf(va_arg(*ap, int)));
	if (c == 'u')
		return (ft_putnbr_base_pf(va_arg(*ap, unsigned int), DEC, 10));
	if (c == 'x')
		return (ft_putnbr_base_pf(va_arg(*ap, unsigned int), HEX_LOW, 16));
	if (c == 'X')
		return (ft_putnbr_base_pf(va_arg(*ap, unsigned int), HEX_UP, 16));
	if (c == '%')
		return (ft_putchar_pf('%'));
	if (ft_putchar_pf('%') == -1 || ft_putchar_pf(c) == -1)
		return (-1);
	return (2);
}

static int	ft_check_format(const char *format)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (0);
		}
		format++;
	}
	return (1);
}

static int	ft_process(const char *format, va_list *ap)
{
	int	count;
	int	ret;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret = ft_dispatch(*format, ap);
		}
		else
			ret = ft_putchar_pf(*format);
		if (ret == -1)
			return (-1);
		count += ret;
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format || !ft_check_format(format))
		return (-1);
	va_start(ap, format);
	count = ft_process(format, &ap);
	va_end(ap);
	return (count);
}
