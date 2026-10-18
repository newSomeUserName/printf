/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_out(t_pf *pf, const char *s, int len)
{
	if (pf->error || len <= 0)
		return ;
	if (write(1, s, len) == -1)
		pf->error = 1;
	else
		pf->count += len;
}

void	ft_pad(t_pf *pf, char c, int n)
{
	while (n > 0)
	{
		ft_out(pf, &c, 1);
		n--;
	}
}

int	ft_numlen(unsigned long long n, int base_len)
{
	int	len;

	len = 1;
	while (n >= (unsigned long long)base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

void	ft_putnbr_base_b(t_pf *pf, unsigned long long n, char *base,
		int base_len)
{
	if (n >= (unsigned long long)base_len)
		ft_putnbr_base_b(pf, n / base_len, base, base_len);
	ft_out(pf, &base[n % base_len], 1);
}
