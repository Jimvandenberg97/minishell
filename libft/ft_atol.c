/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:19:02 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/11/16 11:36:58 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long long			ft_atol(const char *str)
{
	long long	total;
	int			multi;

	total = 0;
	multi = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n' ||
		*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		multi = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total *= 10;
		total += *str - '0';
		if ((total * multi < LLONG_MIN) || (total * multi > LLONG_MAX))
			return ((total * multi < LLONG_MIN) - 1);
		str++;
	}
	return (total * multi);
}
