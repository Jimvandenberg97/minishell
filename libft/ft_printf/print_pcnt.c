/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_pcnt.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 17:48:12 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:46:45 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

void			print_pcnt(t_config *cfg)
{
	cfg->i++;
	if (cfg->min)
		cfg->padd_char = ' ';
	else if (cfg->zero == 1)
		cfg->padd_char = '0';
	if (cfg->min)
		write(1, "%", 1);
	print_padd(cfg->padd_char, cfg->width - 1);
	if (!cfg->min)
		write(1, "%", 1);
	if (cfg->width == 0)
		cfg->width = 1;
	cfg->len += cfg->width;
}
