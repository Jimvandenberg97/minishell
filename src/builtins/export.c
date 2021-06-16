/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 11:51:43 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 12:33:14 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "environment.h"

static void		swap(char **arg1, char **arg2)
{
	char *tmp;

	tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}

static void		sort(char *args[], size_t len)
{
	size_t	i;
	size_t	pvt;

	if (len <= 1)
		return ;
	pvt = 0;
	swap(args + 1, args + len - 1);
	i = 0;
	while (i < len - 1)
	{
		if (ft_strcmp(args[i], args[len - 1]) < 0)
		{
			swap(args + i, args + pvt);
			pvt++;
		}
		i++;
	}
	swap(args + pvt, args + len - 1);
	sort(args, pvt);
	pvt++;
	sort(args + pvt, len - pvt);
}

static char		*prepare(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	var[i] = '\0';
	return (var + i + 1);
}

int				export_empty(t_env *env)
{
	size_t	len;
	t_env	*new;
	char	*value;

	len = 0;
	while (env->vars[len] != NULL)
		len++;
	new = env_init(env->vars);
	if (new == NULL)
		return (EXIT_FAILURE);
	sort(new->vars, len);
	len = 0;
	while (new->vars[len] != NULL)
	{
		value = prepare(new->vars[len]);
		ft_printf("declare -x %s=\"%s\"\n", new->vars[len], value);
		len++;
	}
	env_free(new);
	return (EXIT_SUCCESS);
}
