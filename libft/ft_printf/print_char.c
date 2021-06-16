/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 17:53:55 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:46:23 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

void			ft_print_char(t_config *cfg, va_list ap)
{
	char	c;

	cfg->i++;
	c = (char)va_arg(ap, int);
	if (cfg->min)
		cfg->len += write(1, &c, 1);
	cfg->len += print_padd(cfg->padd_char, cfg->width - 1);
	if (!cfg->min)
		cfg->len += write(1, &c, 1);
}
