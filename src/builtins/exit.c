/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 18:16:43 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/07 14:57:41 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <libft.h>
#include <unistd.h>
#include "messages.h"
#include "ui.h"
#include "builtins.h"

static int	num_valid(char *str, int neg, size_t *i)
{
	size_t	j;
	char	llong[19];
	size_t	x;

	x = 0;
	while (ft_isdigit(str[*i + x]))
		x++;
	if (x == 0)
		return (-2);
	if (x <= 19)
		*i += x;
	if (x < 19)
		return (1);
	ft_strlcpy(llong, EXIT_MAX, 18);
	if (neg)
		llong[18] = '8';
	j = 0;
	while (ft_isdigit(str[*i]) && llong[j] != '\0' && str[*i] <= llong[j])
	{
		(*i)++;
		j++;
	}
	return (!ft_isdigit(str[*i]));
}

static int	arg_valid(char *str)
{
	size_t	i;
	int		neg;
	int		ret;
	int		skip;

	i = 0;
	neg = 0;
	while (str[i] == ' ')
		i++;
	neg = str[i] == '-';
	i += str[i] == '+' || str[i] == '-';
	skip = 0;
	while (str[i] == '0')
	{
		skip = 1;
		i++;
	}
	ret = num_valid(str, neg, &i);
	if (ret != 1 && !(ret == -2 && skip))
		return (ret);
	while (str[i] == ' ')
		i++;
	return (i == ft_strlen(str));
}

static int	is_numeric(char *str)
{
	size_t i;

	if (ft_strlen(str) < 1)
		return (0);
	i = 0;
	i += str[i] == '+' || str[i] == '-';
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int			builtin_exit(char **args, t_env *env)
{
	long long	ret;
	int			av;

	write(STDERR_FILENO, "exit\n", 5);
	ret = env->last_status;
	if (args[1] != NULL && args[2] != NULL)
	{
		if (is_numeric(args[1]))
			printerror(MSG_TOO_MANY_ARGS, ERROR, 1);
		else
			printerror(MSG_TOO_MANY_ARGS, ERROR, 255);
	}
	if (args[1] != NULL)
	{
		av = arg_valid(args[1]);
		if (av == 0 || av == -2)
			printerror(MSG_EXIT_INVALID, WARNING, 255);
		if (av == -1)
			printerror(MSG_MEMORY, ERROR, EXIT_FAILURE);
		ret = ft_atol(args[1]);
	}
	exit(ret % 256);
}
