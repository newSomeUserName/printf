

#include "ft_printf.h"



// int ft_print_special(const char *format, int *count)
// {
// 	char	*specificators;
// 	char	*created;
// 	size_t	start;
// 	size_t	end;

// 	start = 1;
// 	end = 1;
// 	specificators = "cspdiuxX%";
// 	while (format[end] && ft_strchr(specificators, format[end]) == NULL)
// 		end++;
// 	if (!format[end])
// 		return (-1);
// 	if (format[end] == '%')
// 		ft_putchar_fd('%',1);
// 	else
// 	{
// 		created = ft_substr(format, start, end);
// 		ft_putstr_fd(created,1);
// 		*count = *count + 1;
// 	}
// 	return (end + start);
// }




// void ft_check_args_count(const char *format, int params_count)
// {

// }


// void ft_disptch_str(const char *format)
// {
// 	int	next_step;
// 	int	count_special;

// 	count_special = 0;
// 	while (*format)
// 	{
// 		if (*format != '%')
// 		{
// 			ft_putchar_fd(*format,1);
// 			format++;
// 		}
// 		else
// 		{
// 			next_step = ft_print_special(format, &count_special);
// 			if (next_step == -1)
// 				return;
// 			format += next_step;
// 		}
// 	}
// 	ft_putnbr_fd(count_special, 1);
// }


// int	ft_get_params_count(va_list ap)
// {

// }



int ft_get_special_count(const char *format, int *count)
{
	char	*specificators;
	// char	*created;
	size_t	start;
	size_t	end;

	start = 1;
	end = 1;
	specificators = "cspdiuxX%";
	while (format[end] && ft_strchr(specificators, format[end]) == NULL)
		end++;
	if (!format[end])
		return (-1);
	if (format[end] != '%')
		*count = *count + 1;
	return (end + start);
}

int ft_count_special(const char *format)
{
	int	next_step;
	int	spcl_cnt;

	spcl_cnt = 0;
	while (*format)
	{
		if (*format == '%')
		{
			next_step = ft_get_special_count(format, &spcl_cnt);
			if (next_step == -1)
				return (-1);
			format += next_step;
		}
		else
			format++;
	}
	return (spcl_cnt);
}

void ft_print_str(const char *s)
{
	if (s == NULL)
		ft_putstr_fd("(null)",1);
	else
		ft_putstr_fd((char *)s,1);
}


int	ft_putnbr_base(unsigned long n, char *base)
{
        unsigned long   len;
        int                             count;

        len = ft_strlen(base);
        count = 0;
        if (n >= len)
                count += ft_putnbr_base(n / len, base);
        ft_putchar_fd(base[n % len], 1);
        return (count + 1);
}


char *ft_choose_base(char base_selector)
{
	if (base_selector == 'x' || base_selector == 'p')
		return ("0123456789abcdef");
	else if(base_selector == 'X')
		return ("0123456789ABCDEF");
	return ("0123456789");

}
void ft_print_ptr(void *ptr, char c)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)",1);
		return ;
	}
	ft_putstr_fd("0x", 1);
	ft_putnbr_base((unsigned long)ptr, ft_choose_base(c));
}

void ft_print_param(const char *str, va_list ap)
{
	if (str[0] == 'd' || str[0] == 'i')
		ft_putnbr_fd(va_arg(ap, int),1);
	if (str[0] == 's')
		ft_print_str(va_arg(ap, char *));
	if (str[0] == 'p')
		ft_print_ptr(va_arg(ap, void *), str[0]);
	if (str[0] == 'u' || str[0] == 'x' || str[0] == 'X')
		ft_putnbr_base(va_arg(ap, unsigned int), ft_choose_base(str[0]));
	if (str[0] == 'c')
		ft_putchar_fd((char)va_arg(ap, int),1);

}



int ft_dispatch_str(const char *format, va_list ap)
{
	char	*specificators;
	char	*created;
	size_t	start;
	size_t	end;

	start = 1;
	end = 1;
	specificators = "cspdiuxX%";
	while (format[end] && ft_strchr(specificators, format[end]) == NULL)
		end++;
	if (!format[end])
		return (-1);
	if (format[end] == '%')
		ft_putchar_fd('%',1);
	else
	{
		created = ft_substr(format, start, end);
		ft_print_param(created,ap);
		free(created);
	}
	return (end + start);
}



int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int	next_step;

	va_start(ap, format);

	while (*format)
	{
		if (*format == '%')
		{
			next_step = ft_dispatch_str(format, ap);
			if (next_step == -1)
				return (-1);
			format += next_step;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			format++;
		}
	}
	return (0);
}




// int	ft_printf(const char *format, ...)
// {
// 	va_list	ap;
// 	va_list	cpy;
// 	int		special_count;

// 	special_count = ft_count_special(format);
// 	ft_putnbr_fd(special_count, 1);

// 	return (0);
// }


// int		params_count;

// va_start(ap, format);
// va_copy(cpy, ap);

// ft_putnbr_fd(va_arg(ap,int),1);
