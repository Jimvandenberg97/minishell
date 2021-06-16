/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 15:52:00 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:00:17 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "executer.h"
#include "ui.h"
#include "messages.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <libft.h>

/*
** Redirect output of current program to the FD that's assigned for redirection.
*/

static int	handle_output(t_exec *exec, t_partlist *next)
{
	int		tmp;

	if (exec->redir_out >= 0)
	{
		if (ft_dup2(exec->redir_out, STDOUT_FILENO) == -1)
			exiterror(MSG_DUP, ERROR, 1, exec);
		tmp = fd_close(exec->redir_out);
		if (next != NULL)
		{
			tmp += fd_close(exec->pipe_next[PIPE_IN]);
			tmp += fd_close(exec->pipe_next[PIPE_OUT]);
		}
		if (tmp < 0)
			exit(fd_closeall(exec));
	}
	else if (next != NULL)
	{
		if (ft_dup2(exec->pipe_next[PIPE_OUT], STDOUT_FILENO) == -1)
			exiterror(MSG_DUP, ERROR, 1, exec);
		tmp = fd_close(exec->pipe_next[PIPE_IN]);
		tmp += fd_close(exec->pipe_next[PIPE_OUT]);
		if (tmp < 0)
			exit(fd_closeall(exec));
	}
	return (EXIT_SUCCESS);
}

static int	handle_input(t_exec *exec)
{
	int		tmp;

	if (exec->redir_in >= 0)
	{
		if (ft_dup2(exec->redir_in, STDIN_FILENO) == -1)
			exiterror(MSG_DUP, ERROR, 1, exec);
		tmp = fd_close(exec->redir_in);
		if (exec->index != 0)
		{
			tmp += fd_close(exec->pipe_prev[PIPE_IN]);
			tmp += fd_close(exec->pipe_prev[PIPE_OUT]);
		}
		if (tmp < 0)
			exit(fd_closeall(exec));
	}
	else if (exec->index != 0)
	{
		if (ft_dup2(exec->pipe_prev[PIPE_IN], STDIN_FILENO) == -1)
			exiterror(MSG_DUP, ERROR, 1, exec);
		tmp = fd_close(exec->pipe_prev[PIPE_IN]);
		tmp += fd_close(exec->pipe_prev[PIPE_OUT]);
		if (tmp < 0)
			exit(fd_closeall(exec));
	}
	return (EXIT_SUCCESS);
}

static int	exec_fail(t_exec *exec)
{
	printerror(MSG_FORK, ERROR, 0);
	return (fd_closeall(exec));
}

static void	report(char *msg, char *desc)
{
	printerror_prefix(ERROR);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, " ", 1);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, "\n", 1);
}

int			exec_run(char **args, t_exec *exec, t_env *env, t_partlist *next)
{
	signals_init_fork();
	exec->pid = fork();
	if (exec->pid == 0)
	{
		handle_output(exec, next);
		handle_input(exec);
		builtins_fork(args, env);
		if (args[0] == NULL)
			exit(0);
		exec->path = env_file_resolve(env, args[0]);
		if (exec->path == NULL)
		{
			report(MSG_NOT_FOUND, args[0]);
			exit(127);
		}
		execve(exec->path, args, env->vars);
		report(MSG_EXECVE, strerror(errno));
		exit(EXIT_FAILURE);
	}
	else if (exec->pid < 0)
		return (exec_fail(exec));
	return (EXIT_SUCCESS);
}
