/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 11:36:40 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 12:58:37 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <libft.h>
#include <unistd.h>
#include "messages.h"
#include "ui.h"
#include "builtins.h"

int		builtin_export(char **args, t_env *env)
{
	size_t	i;
	int		ret;

	i = 1;
	if (args[1] == NULL)
		return (export_empty(env));
	ret = EXIT_SUCCESS;
	while (args[i] != NULL)
	{
		if (ft_strlen(args[i]) == 0 || env_set(env, args[i]) != 1)
		{
			printerror_prefix(ERROR);
			write(STDERR_FILENO, "Export `", 8);
			write(STDERR_FILENO, args[i], ft_strlen(args[i]));
			write(STDERR_FILENO, "` not valid.\n", 14);
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}

int		builtin_unset(char **args, t_env *env)
{
	size_t	i;
	size_t	codes;

	i = 1;
	codes = 0;
	while (args[i] != NULL)
	{
		codes += env_unset(env, args[i]);
		i++;
	}
	if (codes > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		builtin_env(char **args, t_env *env)
{
	size_t i;

	(void)args;
	i = 0;
	while (env->vars[i] != NULL)
	{
		ft_printf("%s\n", env->vars[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
