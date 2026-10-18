/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_set_flag(char c, t_fmt *f)
{
	if (c == '-')
		f->minus = 1;
	else if (c == '0')
		f->zero = 1;
	else if (c == '#')
		f->hash = 1;
	else if (c == ' ')
		f->space = 1;
	else if (c == '+')
		f->plus = 1;
}

const char	*ft_parse(const char *s, t_fmt *f)
{
	ft_bzero(f, sizeof(t_fmt));
	f->prec = -1;
	while (*s && ft_strchr("-0# +", *s))
	{
		ft_set_flag(*s, f);
		s++;
	}
	while (ft_isdigit(*s))
	{
		f->width = f->width * 10 + (*s - '0');
		s++;
	}
	if (*s == '.')
	{
		s++;
		f->prec = 0;
		while (ft_isdigit(*s))
		{
			f->prec = f->prec * 10 + (*s - '0');
			s++;
		}
	}
	f->conv = *s;
	return (s);
}
