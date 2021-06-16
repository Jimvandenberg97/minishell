/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_pointer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:39:13 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:51:04 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <unistd.h>

static int		ft_gethexlen(long long num)
{
	int		size;

	size = 1;
	if (num >= 16)
		size += ft_gethexlen(num / 16);
	return (size);
}

static int		ft_gettotallen(t_config *cfg, int numlen, long long num)
{
	int			abs_prec;

	abs_prec = cfg->prec < 0 ? cfg->prec * -1 : cfg->prec;
	if (abs_prec > numlen)
	{
		if (cfg->min && cfg->prec < 0)
			return (numlen);
		if (num < 0)
			abs_prec++;
		return (abs_prec);
	}
	else
		return (numlen);
}

static int		ft_puthex(long long num)
{
	char	c;
	int		res;

	res = 0;
	if (num >= 16)
		res += ft_puthex(num / 16);
	c = CHARSET_BASE[num % 16] | 32;
	res += write(1, &c, 1);
	return (res);
}

void			ft_print_pointer(t_config *cfg, va_list ap)
{
	long long	num;
	int			numlen;
	int			total;

	cfg->i++;
	num = (long long)va_arg(ap, void *);
	numlen = ft_gethexlen(num);
	total = ft_gettotallen(cfg, numlen, num) + 2;
	if (!cfg->min)
		cfg->len += print_padd(cfg->padd_char, cfg->width - total);
	cfg->len += write(1, "0x", 2);
	cfg->len += ft_puthex(num);
	if (cfg->min)
		cfg->len += print_padd(' ', cfg->width - total);
}
