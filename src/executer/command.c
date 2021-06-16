/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 10:24:48 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/03 12:32:45 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "executer.h"
#include "parser.h"
#include "environment.h"

char		*exec_arg_parse(t_env *env, t_selem *elem)
{
	char	*result;
	char	*var;
	t_selem	*tmp;

	result = ft_calloc(1, sizeof(char));
	if (result == NULL)
		return (NULL);
	tmp = elem;
	while (tmp != NULL && token_isstring(tmp))
	{
		if (tmp->type == ENVVAR && ft_strcmp(tmp->str, "?") == 0)
			result = ft_strjoin_free12(result, ft_itoa(env->last_status));
		else if (tmp->type == ENVVAR)
		{
			var = env_get(env, tmp->str);
			if (var != NULL)
				result = ft_strjoin_free1(result, var);
		}
		else
			result = ft_strjoin_free1(result, tmp->str);
		if (result == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	return (result);
}

int			command_gen_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	return (0);
}

static int	array_len(t_selem **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int			command_gen(t_env *env, t_exec *exec, t_parser_command *cmd)
{
	size_t	i;
	size_t	j;

	exec->args = ft_calloc(array_len(cmd->args) + 1, sizeof(char *));
	if (exec->args == NULL)
		return (0);
	i = 0;
	j = 0;
	while (cmd->args[i] != NULL)
	{
		exec->args[j] = exec_arg_parse(env, cmd->args[i]);
		if (exec->args[j] == NULL)
			return (command_gen_free(exec->args));
		if (!(ft_strlen(exec->args[j]) == 0 && cmd->args[i]->type == ENVVAR))
			j++;
		else if (exec->args[j] != NULL)
		{
			free(exec->args[j]);
			exec->args[j] = NULL;
		}
		i++;
	}
	return (1);
}
