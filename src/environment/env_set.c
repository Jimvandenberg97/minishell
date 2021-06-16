/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 14:32:45 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/23 15:09:21 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <libft.h>

static int	env_append(t_env *env, char *string)
{
	char	**env_new;
	char	*var;
	size_t	cnt;

	if (string == NULL)
		return (EXIT_FAILURE);
	var = ft_strdup(string);
	if (var == NULL)
		return (EXIT_FAILURE);
	cnt = env_count(env->vars);
	env_new = ft_calloc(cnt + 2, sizeof(char*));
	if (env_new == NULL)
	{
		free(var);
		return (EXIT_FAILURE);
	}
	ft_memmove(env_new, env->vars, cnt * sizeof(char*));
	env_new[cnt] = var;
	free(env->vars);
	env->vars = env_new;
	return (EXIT_SUCCESS);
}

static int	env_validate_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0)
		{
			if (ft_isalpha(str[i]) == 0 && str[i] != '_' && str[i] != '?')
				return (0);
		}
		else
		{
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	env_loop(t_env *env, char *new, int i, char *str)
{
	char	*key;

	if (new[i] == '\0')
	{
		free(new);
		return (env_validate_key(str));
	}
	new[i] = '\0';
	key = new;
	if (env_validate_key(key) == 0)
	{
		free(new);
		return (0);
	}
	if (env_get(env, key) != NULL)
	{
		if (env_unset(env, key) == 1)
		{
			free(new);
			return (1);
		}
	}
	return (-1);
}

int			env_set(t_env *env, char *str)
{
	char	*new;
	int		ret;
	size_t	i;

	new = ft_strdup(str);
	if (new == NULL)
		return (0);
	if (new[0] == '=')
	{
		free(new);
		return (0);
	}
	i = 0;
	while (new[i] != '\0' && new[i] != '=')
		i++;
	ret = env_loop(env, new, i, str);
	if (ret != -1)
		return (ret);
	ret = env_append(env, str);
	free(new);
	return (ret == 0);
}
