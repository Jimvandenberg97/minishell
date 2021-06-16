/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_num.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:39:13 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:50:25 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <unistd.h>

static int		ft_gettotallen(t_config *cfg, int numlen, long num)
{
	int			abs_prec;

	abs_prec = cfg->prec < 0 ? cfg->prec * -1 : cfg->prec;
	if (abs_prec >= numlen)
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

static void		ft_minus(t_config *cfg, long *num, int *numlen, int total)
{
	if (!cfg->min && cfg->padd_char != '0')
		cfg->len += print_padd(cfg->padd_char, cfg->width - total);
	if (*num < 0)
	{
		cfg->len += write(1, "-", 1);
		*num *= -1;
		*numlen = *numlen - 1;
	}
	if (!cfg->min && cfg->padd_char == '0')
		cfg->len += print_padd(cfg->padd_char, cfg->width - total);
}

void			ft_print_num(t_config *cfg, va_list ap)
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
	num = va_arg(ap, int);
	numlen = ft_getnumlen(num, 10);
	total = ft_gettotallen(cfg, numlen, num);
	if (cfg->prec_zero == 1 && num == 0)
		return (print_clear(cfg));
	ft_minus(cfg, &num, &numlen, total);
	if (cfg->prec > 0 && abs_prec > numlen)
		cfg->len += print_padd('0', abs_prec - numlen);
	cfg->len += ft_putint_base(num, 10, 0);
	if (cfg->min)
		cfg->len += print_padd(' ', cfg->width - total);
}
