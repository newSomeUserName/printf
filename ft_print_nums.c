#include "ft_printf.h"

int	ft_putnbr_base(unsigned long n, char *base)
{
	unsigned long	len;
	int				count;

	len = ft_strlen(base);
	count = 0;
	if (n >= len)
		count += ft_putnbr_base(n / len, base);
	ft_putchar_fd(base[n % len], 1);
	return (count + 1);
}

int	ft_print_int(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		count++;
		n = -n;
	}
	count += ft_putnbr_base(n, "0123456789");
	return (count);
}

char	*ft_choose_base(char base_selector)
{
	if (base_selector == 'x' || base_selector == 'p')
		return ("0123456789abcdef");
	else if (base_selector == 'X')
		return ("0123456789ABCDEF");
	return ("0123456789");
}

int	ft_print_ptr(void *ptr, char c)
{
	int	count;

	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	count = 2;
	count += ft_putnbr_base((unsigned long)ptr, ft_choose_base(c));
	return (count);
}
