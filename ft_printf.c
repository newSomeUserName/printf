

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	va_list cpy;

	va_start(ap, format);
	va_copy(cpy, ap);
	ft_putnbr_fd(va_arg(ap,int),1);
	ft_putnbr_fd(va_arg(ap,int),1);




	return (0);
}

size_t ft_args_count(const char *format)
{

}



