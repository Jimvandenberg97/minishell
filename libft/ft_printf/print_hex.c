/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:39:13 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:50:07 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <unistd.h>

static int		ft_gethexlen(unsigned int num)
{
	int		size;

	size = 1;
	if (num >= 16)
		size += ft_gethexlen(num / 16);
	return (size);
}

static int		ft_gettotallen(t_config *cfg, int numlen, long num)
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

static int		ft_puthex(unsigned int num, int upper)
{
	char	c;
	int		res;

	res = 0;
	if (num >= 16)
		res += ft_puthex(num / 16, upper);
	c = CHARSET_BASE[num % 16];
	if (upper == 0)
		c |= 32;
	res += write(1, &c, 1);
	return (res);
}

void			ft_print_hex(const char *format, t_config *cfg, va_list ap)
{
	long		num;
	int			numlen;
	int			abs_prec;
	int			upper;
	int			total;

	cfg->i++;
	upper = format[cfg->i - 1] == 'X';
	if (cfg->prec_neg)
		return (ft_error(cfg));
	if (cfg->prec_zero == 1 && cfg->padd_char == '0')
		cfg->padd_char = ' ';
	abs_prec = cfg->prec < 0 ? cfg->prec * -1 : cfg->prec;
	num = va_arg(ap, unsigned int);
	numlen = ft_gethexlen(num);
	total = ft_gettotallen(cfg, numlen, num);
	if (cfg->prec_zero == 1 && num == 0)
		return (print_clear(cfg));
	if (!cfg->min)
		cfg->len += print_padd(cfg->padd_char, cfg->width - total);
	if (cfg->prec > 0 && abs_prec > numlen)
		cfg->len += print_padd('0', abs_prec - numlen);
	cfg->len += ft_puthex(num, upper);
	if (cfg->min)
		cfg->len += print_padd(' ', cfg->width - total);
}
