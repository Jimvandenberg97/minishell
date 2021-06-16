/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 12:31:45 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:05:46 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <unistd.h>
#include <libft.h>

size_t	env_count(char **envp)
{
	size_t	cnt;

	cnt = 0;
	while (envp[cnt] != NULL)
		cnt++;
	return (cnt);
}

void	env_free_vars(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->vars[i] != NULL)
	{
		free(env->vars[i]);
		i++;
	}
	free(env->vars);
}

void	env_free(t_env *env)
{
	env_free_vars(env);
	free(env);
}

t_env	*env_init(char *envp[])
{
	t_env	*env;
	size_t	i;

	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->vars = ft_calloc(env_count(envp) + 1, sizeof(char*));
	if (env->vars == NULL)
	{
		free(env);
		return (NULL);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		env->vars[i] = ft_strdup(envp[i]);
		if (env->vars[i] == NULL)
		{
			env_free(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
