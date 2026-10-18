/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include "libft/libft.h"

# define DEC "0123456789"
# define HEX_LOW "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"

typedef struct s_pf
{
	va_list	ap;
	int		count;
	int		error;
}	t_pf;

typedef struct s_fmt
{
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		prec;
	char	conv;
}	t_fmt;

int			ft_printf(const char *format, ...);
const char	*ft_parse(const char *s, t_fmt *f);
void		ft_out(t_pf *pf, const char *s, int len);
void		ft_pad(t_pf *pf, char c, int n);
int			ft_numlen(unsigned long long n, int base_len);
void		ft_putnbr_base_b(t_pf *pf, unsigned long long n, char *base,
				int base_len);
void		ft_print_char(t_pf *pf, t_fmt *f, char c);
void		ft_print_str(t_pf *pf, t_fmt *f, char *s);
void		ft_print_int(t_pf *pf, t_fmt *f, int n);
void		ft_print_unsigned(t_pf *pf, t_fmt *f, unsigned int n);
void		ft_print_ptr(t_pf *pf, t_fmt *f, void *ptr);

#endif
