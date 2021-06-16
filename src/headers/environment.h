/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 12:29:55 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:56:19 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>

typedef struct	s_env {
	char		**vars;
	int			last_status;
	int			debug;
	int			argc;
	char		**argv;
}				t_env;

extern t_env	*g_env;

/*
** Initialization
*/

t_env			*env_init(char *envp[]);
void			env_free(t_env *env);
void			env_free_vars(t_env *env);
size_t			env_count(char *envp[]);

/*
** Controls
*/

char			*env_get(t_env *env, char *key);
int				env_set(t_env *env, char *str);
int				env_unset(t_env *env, char *key);

/*
** Path
*/

char			*env_file_resolve(t_env *env, char *file);

#endif
