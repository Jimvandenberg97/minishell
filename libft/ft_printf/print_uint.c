/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_uint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:39:13 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:51:19 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <unistd.h>

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

static int		ft_getuintlen(unsigned int num)
{
	int		len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

void			ft_print_uint(t_config *cfg, va_list ap)
{
	long		num;
	int			numlen;
	int			abs_prec;
	int			total;

	cfg->i++;
	if (cfg->prec_neg)
		return (ft_error(cfg));
	if (cfg->prec_zero == 1 && cfg->padd_char == '0')
		cfg->padd_char = ' ';
	abs_prec = cfg->prec < 0 ? cfg->prec * -1 : cfg->prec;
	num = va_arg(ap, unsigned int);
	numlen = ft_getuintlen(num);
	total = ft_gettotallen(cfg, numlen, num);
	if (cfg->prec_zero == 1 && num == 0)
		return (print_clear(cfg));
	if (!cfg->min)
		cfg->len += print_padd(cfg->padd_char, cfg->width - total);
	if (cfg->prec > 0 && abs_prec > numlen)
		cfg->len += print_padd('0', abs_prec - numlen);
	cfg->len += ft_putnbr_base(num, 10, 0, 0);
	if (cfg->min)
		cfg->len += print_padd(' ', cfg->width - total);
}
