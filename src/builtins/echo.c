/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 18:36:19 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/26 14:27:28 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "environment.h"

static int	isn(char *arg)
{
	size_t	i;

	if (ft_strlen(arg) < 2 || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (i + 1 != ft_strlen(arg));
}

int			builtin_echo(char **args, t_env *env)
{
	int		newline;
	size_t	i;
	char	*space;

	(void)env;
	newline = 1;
	i = 1;
	while (args[i] != NULL && isn(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		space = " ";
		if (args[i + 1] == NULL)
			space = "";
		ft_printf("%s%s", args[i], space);
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
