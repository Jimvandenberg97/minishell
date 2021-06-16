/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_control.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:02:50 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:05:25 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "messages.h"
#include "ui.h"
#include <libft.h>

static char	*env_get_value(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '=')
		i++;
	i++;
	return (&string[i]);
}

static int	env_compare(char *string, char *key)
{
	size_t i;

	i = 0;
	while (string[i] == key[i] && string[i] != '\0' &&
		key[i] != '\0' && string[i] != '=')
	{
		i++;
	}
	return (key[i] == '\0' && string[i] == '=');
}

char		*env_get(t_env *env, char *key)
{
	size_t	pos;
	char	*result;

	pos = 0;
	if (env == NULL)
		return (NULL);
	if (ft_strlen(key) == 1 && ft_isdigit(key[0]))
	{
		if (key[0] - '1' >= env->argc)
			return (NULL);
		else
			return (env->argv[key[0] - '0']);
	}
	while (env->vars[pos] != NULL)
	{
		if (env_compare(env->vars[pos], key))
		{
			result = env_get_value(env->vars[pos]);
			return (result);
		}
		pos++;
	}
	return (NULL);
}

static void	env_loop(t_env *env, char *key, char **env_new, size_t *pos)
{
	if (env_compare(env->vars[pos[1]], key))
	{
		free(env->vars[pos[1]]);
		pos[1]++;
	}
	else
	{
		env_new[pos[0]] = env->vars[pos[1]];
		pos[1]++;
		pos[0]++;
	}
}

int			env_unset(t_env *env, char *key)
{
	size_t	pos[2];
	size_t	cnt;
	char	*var;
	char	**env_new;

	var = env_get(env, key);
	if (var == NULL)
		return (EXIT_FAILURE);
	cnt = env_count(env->vars);
	env_new = ft_calloc(cnt, sizeof(char*));
	if (env_new == NULL)
		return (EXIT_FAILURE);
	pos[0] = 0;
	pos[1] = 0;
	while (env->vars[pos[1]] != NULL)
	{
		env_loop(env, key, env_new, pos);
	}
	free(env->vars);
	env->vars = env_new;
	return (0);
}
