#include "ft_printf.h"

int	ft_print_str(const char *s)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd((char *)s, 1);
	return (ft_strlen(s));
}

int ft_putchar_val(const char c, va_list *ap)
{
    int count;
    
    count = 1;
    if (c == 'c')
		ft_putchar_fd((char)va_arg(*ap, int), 1);
    else if(c == '%')
        ft_putchar_fd('%', 1);
    else
    {
        ft_putchar_fd('%', 1);
        ft_putchar_fd(c, 1);
        count++;
    }
    return (count);
}