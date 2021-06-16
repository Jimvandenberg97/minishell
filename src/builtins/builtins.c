/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 11:08:34 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:03:20 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"
#include "executer.h"
#include <libft.h>

/*
** Link output to new FD on redirection
*/

static int	fd_link(t_exec *exec)
{
	if (exec->redir_out >= 0)
	{
		if (ft_dup2(exec->redir_out, STDOUT_FILENO) == -1)
			return (fd_closeall(exec));
		if (fd_close(exec->redir_out) == -1)
			return (fd_closeall(exec));
	}
	return (EXIT_SUCCESS);
}

/*
** Run builtin and make sure all FD's are set correctly and return is saved.
*/

static int	builtin_run(t_exec *exec, t_env *env, int (*func)(char**, t_env*))
{
	int		tmp_in;
	int		tmp_out;

	exec->builtin = 1;
	tmp_out = ft_dup(STDOUT_FILENO);
	tmp_in = ft_dup(STDOUT_FILENO);
	if (tmp_out == -1 || tmp_in == -1)
		return (EXIT_FAILURE);
	if (fd_link(exec) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	env->last_status = func(exec->args, env);
	if (ft_dup2(tmp_out, STDOUT_FILENO) == -1
		|| ft_dup2(tmp_in, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (0 + fd_close(tmp_out) + fd_close(tmp_in) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** Switch for selecting builtin.
** These are local so we return the statuscode instead of an exit() call.
*/

int			builtins_local(char **args, t_exec *exec, t_env *env)
{
	if (args == NULL || args[0] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_run(exec, env, builtin_cd));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_run(exec, env, builtin_echo));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_run(exec, env, builtin_env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_run(exec, env, builtin_export));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_run(exec, env, builtin_unset));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_run(exec, env, builtin_exit));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_run(exec, env, builtin_pwd));
	return (EXIT_SUCCESS);
}

/*
** Search for proper builtin, run, and exit with the statuscode
*/

void		builtins_fork(char **args, t_env *env)
{
	if (args == NULL || args[0] == NULL)
		return ;
	if (ft_strcmp(args[0], "cd") == 0)
		exit(builtin_cd(args, env));
	else if (ft_strcmp(args[0], "echo") == 0)
		exit(builtin_echo(args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		exit(builtin_env(args, env));
	else if (ft_strcmp(args[0], "export") == 0)
		exit(builtin_export(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		exit(builtin_unset(args, env));
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(builtin_exit(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		exit(builtin_pwd(args, env));
}
