/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 11:58:38 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/30 12:13:45 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"

# define EXIT_MAX "9223372036854775807"

int		builtin_cd(char **args, t_env *env);
int		builtin_echo(char **args, t_env *env);
int		builtin_env(char **args, t_env *env);
int		builtin_export(char **args, t_env *env);
int		builtin_unset(char **args, t_env *env);
int		builtin_exit(char **args, t_env *env);
int		builtin_pwd(char **args, t_env *env);

int		export_empty(t_env *env);

#endif
