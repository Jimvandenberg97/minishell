/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:13:58 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 16:41:16 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "parser.h"
#include "environment.h"
#include <unistd.h>
#include <libft.h>
#include <sys/wait.h>

static t_exec	*exec_init(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		return (NULL);
	ft_bzero(exec, sizeof(exec));
	exec->pipe_next[PIPE_IN] = -1;
	exec->pipe_next[PIPE_OUT] = -1;
	exec->pipe_prev[PIPE_IN] = -1;
	exec->pipe_prev[PIPE_OUT] = -1;
	return (exec);
}

void			exit_codes(t_exec *exec, t_env *env)
{
	exec->last_pid = 1;
	while (exec->last_pid > 0)
	{
		exec->last_pid = waitpid(0, &exec->status, WUNTRACED);
		if (exec->last_pid == exec->pid)
		{
			if (WIFEXITED(exec->status))
				env->last_status = WEXITSTATUS(exec->status);
			else if (WIFSIGNALED(exec->status))
			{
				env->last_status = WTERMSIG(exec->status);
				env->last_status += 128;
			}
		}
	}
}

static int		loop(t_env *env, t_exec *exec, t_partlist *list,
					t_cmdlist *layer)
{
	command_gen(env, exec, list->command);
	exec->builtin = 0;
	if (fildescriptors_set(exec, layer->list, list->command, env) ==
		EXIT_FAILURE)
	{
		command_gen_free(exec->args);
		return (EXIT_FAILURE);
	}
	if (layer->list->next == NULL)
		if (builtins_local(exec->args, exec, env) != 0)
		{
			command_gen_free(exec->args);
			return (EXIT_FAILURE);
		}
	if (exec->builtin == 0)
		if (exec_run(exec->args, exec, env, list->next) == EXIT_FAILURE)
		{
			command_gen_free(exec->args);
			return (EXIT_FAILURE);
		}
	filedescriptors_close(exec);
	if (env->debug)
		exec_debug(exec);
	return (EXIT_SUCCESS);
}

static int		exec_layer(t_cmdlist *layer, t_env *env)
{
	t_exec		*exec;
	t_partlist	*list;

	exec = exec_init();
	if (exec == NULL)
		return (0);
	list = layer->list;
	while (list != NULL)
	{
		if (loop(env, exec, list, layer) == EXIT_FAILURE)
		{
			free(exec);
			return (EXIT_FAILURE);
		}
		list = list->next;
		command_gen_free(exec->args);
		exec->index++;
	}
	exit_codes(exec, env);
	free(exec);
	return (1);
}

int				executer(t_parser_state *parser, t_env *env)
{
	t_cmdlist	*layer;
	int			ret;

	layer = parser->result;
	while (layer != NULL)
	{
		ret = exec_layer(layer, env);
		layer = layer->next;
	}
	return (ret);
}
