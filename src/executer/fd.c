/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 12:15:06 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 14:12:31 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "environment.h"
#include "executer.h"
#include "ui.h"
#include "messages.h"
#include <fcntl.h>

int			get_fd_out(t_parser_command *command, t_env *env)
{
	size_t			i;
	t_redirection	*redir;
	char			*path;
	int				fd;

	i = 0;
	while (command->redirects_out[i] != NULL)
	{
		redir = command->redirects_out[i];
		path = exec_arg_parse(env, redir->file);
		if (path == NULL)
			return (-2);
		fd = open(path, O_WRONLY | O_CREAT |
			(redir->type == APPEND ? O_APPEND : O_TRUNC), 0644);
		free(path);
		if (fd == -1)
			return (-1);
		i++;
	}
	if (i == 0)
		fd = -1;
	return (fd);
}

int			get_fd_in(t_parser_command *command, t_env *env)
{
	size_t			i;
	t_redirection	*redir;
	char			*path;
	int				fd;

	if (command->redirects_in == NULL)
		return (-1);
	fd = -1;
	i = 0;
	while (command->redirects_in[i] != NULL)
	{
		redir = command->redirects_in[i];
		path = exec_arg_parse(env, redir->file);
		if (path == NULL)
			return (-2);
		fd = open(path, O_RDONLY);
		free(path);
		if (fd == -1)
			return (-2);
		i++;
	}
	return (fd);
}

int			fd_closeall(t_exec *exec)
{
	struct stat	buf;

	if (fstat(exec->pipe_prev[PIPE_IN], &buf) == 0)
		fd_close(exec->pipe_prev[PIPE_IN]);
	if (fstat(exec->pipe_prev[PIPE_OUT], &buf) == 0)
		fd_close(exec->pipe_prev[PIPE_OUT]);
	if (fstat(exec->pipe_next[PIPE_IN], &buf) == 0)
		fd_close(exec->pipe_next[PIPE_IN]);
	if (fstat(exec->pipe_next[PIPE_OUT], &buf) == 0)
		fd_close(exec->pipe_next[PIPE_OUT]);
	if (exec->redir_in > 2 && fstat(exec->redir_in, &buf) == 0)
		fd_close(exec->redir_in);
	if (exec->redir_out > 2 && fstat(exec->redir_out, &buf) == 0)
		fd_close(exec->redir_out);
	return (EXIT_FAILURE);
}
