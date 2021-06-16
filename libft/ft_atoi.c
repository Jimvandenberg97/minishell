/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:19:02 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/06/29 11:55:49 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int			ft_atoi(const char *str)
{
	long int	total;
	long int	multiplier;

	total = 0;
	multiplier = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n' ||
		*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		multiplier = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total *= 10;
		total += *str - '0';
		if ((total * multiplier < INT_MIN) || (total * multiplier > INT_MAX))
			return ((total * multiplier < INT_MIN) - 1);
		str++;
	}
	return (total * multiplier);
}
