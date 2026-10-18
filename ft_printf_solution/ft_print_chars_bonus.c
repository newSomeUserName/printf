/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_print_char(t_pf *pf, t_fmt *f, char c)
{
	if (!f->minus)
		ft_pad(pf, ' ', f->width - 1);
	ft_out(pf, &c, 1);
	if (f->minus)
		ft_pad(pf, ' ', f->width - 1);
}

void	ft_print_str(t_pf *pf, t_fmt *f, char *s)
{
	int	len;

	if (!s && f->prec >= 0 && f->prec < 6)
		s = "";
	else if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (f->prec >= 0 && f->prec < len)
		len = f->prec;
	if (!f->minus)
		ft_pad(pf, ' ', f->width - len);
	ft_out(pf, s, len);
	if (f->minus)
		ft_pad(pf, ' ', f->width - len);
}
