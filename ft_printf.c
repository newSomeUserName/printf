#include "ft_printf.h"

static int	ft_print_param(const char c, va_list *ap)
{
	int	result;

	if (c == 'd' || c == 'i')
		result = ft_print_int(va_arg(*ap, int));
	else if (c == 's')
		result = ft_print_str(va_arg(*ap, char *));
	else if (c == 'p')
		result = ft_print_ptr(va_arg(*ap, void *), c);
	else if (c == 'u' || c == 'x' || c == 'X')
		result = ft_putnbr_base(va_arg(*ap, unsigned int), ft_choose_base(c));
	else
		result = ft_putchar_val(c,ap);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format)
		return (-1);	
	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && format[1])
		{
			format++;
			count += ft_print_param(*format, &ap);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	va_end(ap);
	return (count);
}
