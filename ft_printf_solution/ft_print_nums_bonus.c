/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nums_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_zeros(t_fmt *f, int ndig, int plen)
{
	if (f->prec > ndig)
		return (f->prec - ndig);
	if (f->prec < 0 && f->zero && !f->minus && f->width > plen + ndig)
		return (f->width - plen - ndig);
	return (0);
}

static void	ft_putnum(t_pf *pf, t_fmt *f, unsigned long long n, char *pre)
{
	char	*base;
	int		ndig;
	int		zeros;
	int		total;

	base = DEC;
	if (f->conv == 'x' || f->conv == 'p')
		base = HEX_LOW;
	else if (f->conv == 'X')
		base = HEX_UP;
	ndig = ft_numlen(n, ft_strlen(base));
	if (f->prec == 0 && n == 0)
		ndig = 0;
	zeros = ft_zeros(f, ndig, ft_strlen(pre));
	total = ft_strlen(pre) + zeros + ndig;
	if (!f->minus)
		ft_pad(pf, ' ', f->width - total);
	ft_out(pf, pre, ft_strlen(pre));
	ft_pad(pf, '0', zeros);
	if (ndig)
		ft_putnbr_base_b(pf, n, base, ft_strlen(base));
	if (f->minus)
		ft_pad(pf, ' ', f->width - total);
}

void	ft_print_int(t_pf *pf, t_fmt *f, int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
		ft_putnum(pf, f, -nb, "-");
	else if (f->plus)
		ft_putnum(pf, f, nb, "+");
	else if (f->space)
		ft_putnum(pf, f, nb, " ");
	else
		ft_putnum(pf, f, nb, "");
}

void	ft_print_unsigned(t_pf *pf, t_fmt *f, unsigned int n)
{
	if (f->hash && n != 0 && f->conv == 'x')
		ft_putnum(pf, f, n, "0x");
	else if (f->hash && n != 0 && f->conv == 'X')
		ft_putnum(pf, f, n, "0X");
	else
		ft_putnum(pf, f, n, "");
}

void	ft_print_ptr(t_pf *pf, t_fmt *f, void *ptr)
{
	t_fmt	nil;

	if (!ptr)
	{
		nil = *f;
		nil.prec = -1;
		ft_print_str(pf, &nil, "(nil)");
	}
	else if (f->plus)
		ft_putnum(pf, f, (unsigned long long)ptr, "+0x");
	else if (f->space)
		ft_putnum(pf, f, (unsigned long long)ptr, " 0x");
	else
		ft_putnum(pf, f, (unsigned long long)ptr, "0x");
}
