/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 18:42:56 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:04:18 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "environment.h"
#include "messages.h"
#include "ui.h"
#include <errno.h>
#include <string.h>
#include <libft.h>

static int		set_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = env_get(env, "PWD");
	if (oldpwd != NULL)
	{
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		if (oldpwd == NULL || !env_set(env, oldpwd))
		{
			free(oldpwd);
			printerror(MSG_CHDIR_PWD, ERROR, 0);
			return (EXIT_FAILURE);
		}
		free(oldpwd);
	}
	else
	{
		if (env_unset(env, "OLDPWD") == EXIT_FAILURE)
		{
			printerror(MSG_CHDIR_PWD, ERROR, 0);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int		set_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printerror(MSG_CHDIR_PWD, ERROR, 0);
		return (EXIT_FAILURE);
	}
	pwd = ft_strjoin_free2("PWD=", pwd);
	if (pwd == NULL || !env_set(env, pwd))
	{
		free(pwd);
		printerror(MSG_CHDIR_PWD, ERROR, 0);
		return (EXIT_FAILURE);
	}
	free(pwd);
	return (EXIT_SUCCESS);
}

int				builtin_cd(char **args, t_env *env)
{
	if (args[1] == NULL)
	{
		printerror(MSG_CD_NULL, ERROR, 0);
		return (EXIT_FAILURE);
	}
	else
	{
		if (ft_strlen(args[1]) == 0)
		{
			free(args[1]);
			args[1] = getcwd(NULL, 0);
		}
		if (chdir(args[1]) != 0)
		{
			printerror(strerror(errno), ERROR, 0);
			return (EXIT_FAILURE);
		}
		if (set_oldpwd(env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (set_pwd(env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
