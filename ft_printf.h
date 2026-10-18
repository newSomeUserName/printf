#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_print_str(const char *s);
int		ft_putnbr_base(unsigned long n, char *base);
int		ft_print_int(long n);
char	*ft_choose_base(char base_selector);
int		ft_print_ptr(void *ptr, char c);
int     ft_putchar_val(const char c, va_list *ap);
#endif
