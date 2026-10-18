/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_check_format(const char *s)
{
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			while (*s && ft_strchr("-0# +.0123456789", *s))
				s++;
			if (!*s)
				return (0);
		}
		s++;
	}
	return (1);
}

static void	ft_dispatch(t_pf *pf, t_fmt *f, const char *start,
		const char *end)
{
	if (f->conv == 'c')
		ft_print_char(pf, f, (char)va_arg(pf->ap, int));
	else if (f->conv == 's')
		ft_print_str(pf, f, va_arg(pf->ap, char *));
	else if (f->conv == 'p')
		ft_print_ptr(pf, f, va_arg(pf->ap, void *));
	else if (f->conv == 'd' || f->conv == 'i')
		ft_print_int(pf, f, va_arg(pf->ap, int));
	else if (f->conv == 'u' || f->conv == 'x' || f->conv == 'X')
		ft_print_unsigned(pf, f, va_arg(pf->ap, unsigned int));
	else if (f->conv == '%')
		ft_out(pf, "%", 1);
	else
		ft_out(pf, start, end - start + 1);
}

int	ft_printf(const char *format, ...)
{
	t_pf		pf;
	t_fmt		f;
	const char	*start;

	if (!format || !ft_check_format(format))
		return (-1);
	pf.count = 0;
	pf.error = 0;
	va_start(pf.ap, format);
	while (*format && !pf.error)
	{
		if (*format == '%')
		{
			start = format;
			format = ft_parse(format + 1, &f);
			ft_dispatch(&pf, &f, start, format);
		}
		else
			ft_out(&pf, format, 1);
		format++;
	}
	va_end(pf.ap);
	if (pf.error)
		return (-1);
	return (pf.count);
}
