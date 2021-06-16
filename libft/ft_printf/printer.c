/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 17:12:56 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:47:03 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int			print_padd(char c, int count)
{
	int	res;

	res = 0;
	while (count > 0)
	{
		res += write(1, &c, 1);
		count--;
	}
	return (res);
}

void		print_clear(t_config *cfg)
{
	if (cfg->prec_zero == 1)
		cfg->len += print_padd(' ', cfg->width);
	return ;
}

void		ft_error(t_config *cfg)
{
	cfg->error = 1;
}

void		printer(const char *format, t_config *cfg, va_list ap)
{
	if (format[cfg->i] == 'd' || format[cfg->i] == 'i')
		ft_print_num(cfg, ap);
	else if (format[cfg->i] == 'x' || format[cfg->i] == 'X')
		ft_print_hex(format, cfg, ap);
	else if (format[cfg->i] == '%')
		print_pcnt(cfg);
	else if (format[cfg->i] == 'c')
		ft_print_char(cfg, ap);
	else if (format[cfg->i] == 's')
		ft_print_string(cfg, ap);
	else if (format[cfg->i] == 'u')
		ft_print_uint(cfg, ap);
	else if (format[cfg->i] == 'p')
		ft_print_pointer(cfg, ap);
}
