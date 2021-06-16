/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:43:51 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:56:49 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parser.h"
# include "environment.h"
# include "ui.h"
# include <sys/types.h>
# include <sys/stat.h>

# define PIPE_IN 0
# define PIPE_OUT 1

typedef struct	s_exec {
	int			builtin;
	int			redir_in;
	int			redir_out;
	pid_t		pid;
	int			pipe_prev[2];
	int			pipe_next[2];
	int			last_pid;
	int			status;
	char		*path;
	char		**args;
	size_t		index;
}				t_exec;

int				executer(t_parser_state *parser, t_env *env);
int				command_gen(t_env *env, t_exec *exec, t_parser_command	*cmd);
int				command_gen_free(char **arr);
char			*exec_arg_parse(t_env *env, t_selem *elem);
int				exec_run(char **args, t_exec *exec, t_env *env,
					t_partlist *list);

/*
** Redirections
*/

int				fildescriptors_set(t_exec *exec, t_partlist *list,
					t_parser_command *command, t_env *env);
int				filedescriptors_close(t_exec *exec);

/*
** File Descriptors
*/

int				get_fd_out(t_parser_command *command, t_env *env);
int				get_fd_in(t_parser_command *command, t_env *env);

/*
** Signals
*/

void			signals_init_interactive(void);
void			signals_init_fork(void);

/*
** Builtins
*/

void			builtins_fork(char **args, t_env *env);
int				builtins_local(char **args, t_exec *exec, t_env *env);

/*
** Utils
*/

int				ft_dup2(int fd1, int fd2);
int				ft_pipe(int *fd);
int				ft_dup(int fd);
int				fd_close(int fd);
int				fd_closeall(t_exec *exec);
void			exiterror(char *msg, t_errortype err, int stop, t_exec *exec);
void			exec_debug(t_exec *exec);

#endif
