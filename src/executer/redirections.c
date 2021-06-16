/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 12:35:39 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 14:36:05 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "ui.h"
#include "messages.h"
#include <sys/stat.h>
#include <unistd.h>

static size_t	list_len(t_partlist *list)
{
	t_partlist	*item;
	size_t		len;

	if (list == NULL)
		return (0);
	len = 0;
	item = list;
	while (item != NULL)
	{
		item = item->next;
		len++;
	}
	return (len);
}

int				fildescriptors_set(t_exec *exec, t_partlist *list,
					t_parser_command *command, t_env *env)
{
	size_t	len;

	len = list_len(list);
	if (len > 1 && exec->index < len - 1 && pipe(exec->pipe_next) == -1)
	{
		env->last_status = 1;
		printerror(MSG_REDIR, ERROR, 0);
		return (fd_closeall(exec));
	}
	exec->redir_in = get_fd_in(command, env);
	if (exec->redir_in == -2)
	{
		env->last_status = 1;
		printerror(MSG_EXEC_FD_IN, ERROR, 0);
		return (fd_closeall(exec));
	}
	exec->redir_out = get_fd_out(command, env);
	if (exec->redir_out == -2)
	{
		env->last_status = 1;
		printerror(MSG_EXEC_FD_OUT, ERROR, 0);
		return (fd_closeall(exec));
	}
	return (EXIT_SUCCESS);
}

int				filedescriptors_close(t_exec *exec)
{
	struct stat	buf;
	int			tmp;

	tmp = 0;
	if (exec->index > 0)
	{
		tmp += fd_close(exec->pipe_prev[PIPE_IN]);
		tmp += fd_close(exec->pipe_prev[PIPE_OUT]);
	}
	exec->pipe_prev[PIPE_IN] = exec->pipe_next[PIPE_IN];
	exec->pipe_prev[PIPE_OUT] = exec->pipe_next[PIPE_OUT];
	if (exec->redir_in > 2 && fstat(exec->redir_in, &buf) == 0)
		tmp += fd_close(exec->redir_in);
	if (exec->redir_out > 2 && fstat(exec->redir_out, &buf) == 0)
		tmp += fd_close(exec->redir_out);
	if (tmp < 0)
		return (fd_closeall(exec));
	return (EXIT_SUCCESS);
}
