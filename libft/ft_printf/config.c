/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 16:00:22 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/05 16:46:12 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

t_config	*cfg_init(void)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (cfg == NULL)
		return (NULL);
	cfg->i = 0;
	cfg->len = 0;
	cfg->error = 0;
	cfg_reset(cfg);
	return (cfg);
}

void		cfg_reset(t_config *cfg)
{
	cfg->padd = 0;
	cfg->padd_dir = '\0';
	cfg->padd_char = ' ';
	cfg->prec = 0;
	cfg->prec_zero = 0;
	cfg->prec_neg = 0;
	cfg->upper = 0;
	cfg->sign = 0;
	cfg->min = 0;
	cfg->width = 0;
	cfg->zero = 0;
}
