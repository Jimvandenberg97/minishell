/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 16:20:48 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/06/29 11:58:51 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_putnbr_base(unsigned long long num, size_t base, int sign, int uc)
{
	unsigned long long	nbr;
	char				c;
	int					len;

	len = 0;
	if (base < 2 || base > 36)
		return (-1);
	if (num >> 63 & 1 && sign)
	{
		if (base == 10)
			len += write(1, "-", 1);
		else
			num &= ~1;
		nbr = (num * -1);
	}
	else
		nbr = num;
	if (nbr >= base)
		len += ft_putnbr_base(nbr / base, base, sign, uc);
	c = CHARSET_BASE[nbr % base];
	if (uc == 0)
		c |= 32;
	len += write(1, &c, 1);
	return (len);
}

int		ft_putint_base(long num, size_t base, int uc)
{
	char	c;
	int		len;

	len = 0;
	if (base < 2 || base > 36)
		return (-1);
	if (num < 0)
	{
		len += write(1, "-", 1);
		num *= -1;
	}
	if (num >= (long)base)
		len += ft_putint_base(num / base, base, uc);
	c = CHARSET_BASE[num % base];
	if (uc == 0)
		c |= 32;
	len += write(1, &c, 1);
	return (len);
}
