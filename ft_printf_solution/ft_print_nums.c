/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:00:00 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/18 16:00:00 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_pf(unsigned long long n, char *base, unsigned int len)
{
	int	count;

	count = 0;
	if (n >= len)
	{
		count = ft_putnbr_base_pf(n / len, base, len);
		if (count == -1)
			return (-1);
	}
	if (ft_putchar_pf(base[n % len]) == -1)
		return (-1);
	return (count + 1);
}

int	ft_putnbr_pf(int n)
{
	long	nb;
	int		sign;
	int		ret;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		if (ft_putchar_pf('-') == -1)
			return (-1);
		nb = -nb;
		sign = 1;
	}
	ret = ft_putnbr_base_pf(nb, DEC, 10);
	if (ret == -1)
		return (-1);
	return (ret + sign);
}

int	ft_putptr_pf(void *ptr)
{
	int	ret;

	if (!ptr)
		return (ft_putstr_pf("(nil)"));
	if (ft_putstr_pf("0x") == -1)
		return (-1);
	ret = ft_putnbr_base_pf((unsigned long long)ptr, HEX_LOW, 16);
	if (ret == -1)
		return (-1);
	return (ret + 2);
}
