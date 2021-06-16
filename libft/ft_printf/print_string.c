/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 17:53:55 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:46:55 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

static int		ft_putstr_max(char *str, int count)
{
	if (count == 0)
		count = ft_strlen(str);
	if (str == NULL && count > 6)
		count = 6;
	if (str == NULL)
		write(1, "(null)", count);
	else
		write(1, str, count);
	return (count);
}

void			ft_print_string(t_config *cfg, va_list ap)
{
	char	*str;
	int		strlen;

	cfg->i++;
	str = va_arg(ap, char *);
	if (cfg->prec_zero == 1)
		return (print_clear(cfg));
	strlen = str == NULL ? 6 : ft_strlen(str);
	if (cfg->prec < 0)
	{
		cfg->len += write(1, str == NULL ? "(null)" : str, strlen);
		return ;
	}
	if (cfg->prec == 0)
		cfg->prec = strlen;
	if (strlen > cfg->prec)
		strlen = cfg->prec;
	if (cfg->min)
		cfg->len += ft_putstr_max(str, strlen);
	cfg->len += print_padd(' ', cfg->width - strlen);
	if (!cfg->min)
		cfg->len += ft_putstr_max(str, strlen);
}
