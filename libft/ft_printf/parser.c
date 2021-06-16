/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:48:03 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:46:19 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <unistd.h>

static void	parse_prec(const char *format, t_config *cfg, va_list ap)
{
	if (!ft_strchr(".*0123456789cspdiuxX%", format[cfg->i]))
		return (ft_error(cfg));
	if (format[cfg->i] == '.')
	{
		cfg->i++;
		if (ft_isdigit(format[cfg->i]) || format[cfg->i] == '-')
		{
			cfg->prec = ft_atoi(&format[cfg->i]);
			if (format[cfg->i] == '-')
			{
				cfg->prec_neg = 1;
				cfg->i++;
			}
			while (ft_isdigit(format[cfg->i]))
				cfg->i++;
		}
		else if (format[cfg->i] == '*')
		{
			cfg->prec = va_arg(ap, int);
			cfg->i++;
		}
		if (cfg->prec == 0)
			cfg->prec_zero = 1;
	}
}

static void	parse_width(const char *format, t_config *cfg, va_list ap)
{
	if (!ft_strchr(".*0123456789cspdiuxX%", format[cfg->i]))
		return (ft_error(cfg));
	if (ft_isdigit(format[cfg->i]))
	{
		cfg->width = ft_atoi(&format[cfg->i]);
		while (ft_isdigit(format[cfg->i]))
			cfg->i++;
	}
	else if (format[cfg->i] == '*')
	{
		cfg->width = va_arg(ap, int);
		if (cfg->width < 0)
			cfg->min = 1;
		cfg->i++;
	}
}

static void	parse_flags(const char *format, t_config *cfg, va_list ap)
{
	while (ft_strchr("-0", format[cfg->i]) && format[cfg->i] != '\0')
	{
		if (format[cfg->i] == '-')
			cfg->min = 1;
		else
		{
			cfg->padd_char = '0';
			cfg->zero = 1;
		}
		cfg->i++;
	}
	parse_width(format, cfg, ap);
	if (cfg->error == 1)
		return ;
	parse_prec(format, cfg, ap);
	if (cfg->error == 1)
		return ;
	if (cfg->prec != 0)
		cfg->padd_char = ' ';
}

void		parse(const char *format, t_config *cfg, va_list ap)
{
	while (format[cfg->i] != '\0')
	{
		if (format[cfg->i] == '%')
		{
			cfg->i++;
			cfg_reset(cfg);
			if (ft_strchr("-.*0123456789", format[cfg->i]))
				parse_flags(format, cfg, ap);
			if (ft_strchr("cspdiuxX%", format[cfg->i]))
			{
				if (cfg->width < 0)
					cfg->width *= -1;
				printer(format, cfg, ap);
			}
			else
				return (ft_error(cfg));
		}
		else
		{
			write(1, &format[cfg->i], 1);
			cfg->len++;
			cfg->i++;
		}
	}
}
