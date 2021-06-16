/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 12:12:32 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:08:08 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <libft.h>

size_t			argv_count(t_selem **args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

size_t			redirect_count(t_redirection **args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

t_selem			**cmd_append_arg(t_selem **args, t_selem *token)
{
	t_selem		**newarr;
	size_t		len;

	len = argv_count(args);
	newarr = ft_calloc(len + 2, sizeof(t_selem*));
	if (newarr == NULL)
		return (0);
	ft_memcpy(newarr, args, len * sizeof(t_selem*));
	newarr[len] = token;
	free(args);
	return (newarr);
}

t_redirection	**cmd_append_redirect(t_redirection **redirects, t_selem *token,
	t_redirection_type type)
{
	t_redirection	*element;
	t_redirection	**newarr;
	size_t			len;

	element = malloc(sizeof(t_redirection));
	if (element == NULL)
		return (NULL);
	element->file = token;
	element->type = type;
	len = redirect_count(redirects);
	newarr = ft_calloc(len + 2, sizeof(t_redirection*));
	if (newarr == NULL)
	{
		free(element);
		return (0);
	}
	ft_memcpy(newarr, redirects, len * sizeof(t_redirection*));
	newarr[len] = element;
	free(redirects);
	return (newarr);
}

void			free_args(t_selem **args)
{
	t_selem *arg;
	t_selem *tmp;

	arg = *args;
	while (arg != NULL)
	{
		tmp = arg->next;
		free(arg->str);
		free(arg);
		arg = tmp;
	}
	free(args);
}
