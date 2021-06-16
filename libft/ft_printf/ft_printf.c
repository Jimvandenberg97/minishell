/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 14:58:27 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:46:16 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int					ft_printf(const char *format, ...)
{
	va_list		ap;
	t_config	*cfg;
	int			len;

	len = ft_strlen(format);
	if (len == 0 || (len == 1 && format[0] == '%'))
		return (0);
	if (ft_strchr(format, '%'))
	{
		cfg = cfg_init();
		if (cfg == NULL)
			return (-1);
		va_start(ap, format);
		parse(format, cfg, ap);
		va_end(ap);
		len = cfg->len;
		if (cfg->error != 0)
			len = -1;
		free(cfg);
		return (len);
	}
	else
		return (write(1, format, len));
}
