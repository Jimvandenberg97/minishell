/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envvar_stepper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/18 12:56:54 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 12:44:33 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ui.h"
#include "messages.h"
#include <unistd.h>
#include <libft.h>

/*
** Only certain chars are valid as first char after a $.
*/

static int	firstchar(char *new, char *old, size_t *pos_new, size_t *pos_old)
{
	if (new == NULL || old == NULL || pos_new == NULL || pos_old == NULL)
	{
		printerror(MSG_IMPOSSIBLE, WARNING, 0);
		return (0);
	}
	if (ft_isalnum(old[*pos_old]) || old[*pos_old] == '_' ||
		old[*pos_old] == '?')
	{
		new[*pos_new] = old[*pos_old];
		(*pos_old)++;
		(*pos_new)++;
		return (1);
	}
	else
	{
		printerror("Invalid environment identifier.", ERROR, 0);
		return (0);
	}
}

/*
** Checker for 2nd and above character after a '$'.
** Chars after the first one are also allowed to be numerical.
*/

static int	otherchars(char *new, char *old, size_t *pos_new, size_t *pos_old)
{
	if (new == NULL || old == NULL || pos_new == NULL || pos_old == NULL)
	{
		printerror(MSG_IMPOSSIBLE, WARNING, 0);
		return (0);
	}
	if (ft_isalnum(old[*pos_old]) || old[*pos_old] == '_')
	{
		new[*pos_new] = old[*pos_old];
		(*pos_old)++;
		(*pos_new)++;
		return (0);
	}
	else
	{
		(*pos_old)--;
		return (1);
	}
}

/*
** Steps over all characters inside an envvar.
** As soon as we encounter an invalid char, we mark this envvar as complete.
*/

int			envvar_step(char *new, char *old, size_t *pos_new, size_t *pos_old)
{
	size_t	i;

	i = 0;
	if (new == NULL || old == NULL || pos_new == NULL || pos_old == NULL)
		printerror(MSG_IMPOSSIBLE, WARNING, 0);
	else
		while (old[*pos_old] != '\0')
		{
			if (i == 0)
			{
				if (firstchar(new, old, pos_new, pos_old) == 0)
					return (0);
				else if (old[(*pos_old) - 1] == '?')
				{
					(*pos_old)--;
					return (1);
				}
				i++;
				continue;
			}
			if (otherchars(new, old, pos_new, pos_old) == 1)
				return (1);
			i++;
		}
	return (0);
}
