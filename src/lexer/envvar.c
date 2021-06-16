/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envvar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 12:07:40 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/07 12:48:00 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ui.h"
#include "messages.h"
#include <libft.h>

/*
** Count the amount of envvars within double quotes.
** We need this to calculate the size for the new string using this formula:
** strlen + count * 2
*/

static size_t	envvars_quot_count(char *str)
{
	size_t	pos;
	size_t	cnt;

	if (str == NULL)
		return (0);
	pos = 0;
	cnt = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] == '"')
		{
			pos++;
			while (!(str[pos] == '"' && escapes_count(str, pos) % 2 == 0))
			{
				if (str[pos] == '\0')
					return (cnt);
				if (str[pos] == '$' && escapes_count(str, pos) % 2 == 0)
					cnt++;
				pos++;
			}
		}
		pos++;
	}
	return (cnt);
}

/*
** Copy over a character from old to new, and increment both counters.
*/

static void		char_copyover(char *newstr, char *oldstr, size_t *pos_new,
	size_t *pos_old)
{
	newstr[*pos_new] = oldstr[*pos_old];
	(*pos_old)++;
	(*pos_new)++;
}

/*
** When inside a quoted string, we try to actually split out the envvar.
*/

static int		inquotes(char *new, char *old, size_t *pos_new, size_t *pos_old)
{
	if (new == NULL || old == NULL || pos_new == NULL || pos_old == NULL)
	{
		printerror(MSG_IMPOSSIBLE, WARNING, 0);
		return (0);
	}
	if (old[*pos_old] == '\0')
		return (0);
	if (escapes_count(old, *pos_old) % 2 == 0 &&
		old[*pos_old] == '$' &&
		(old[*pos_old + 1] == '?' || ft_isalnum(old[*pos_old + 1]) ||
		old[*pos_old + 1] == '_'))
	{
		new[*pos_new] = '"';
		(*pos_new)++;
		char_copyover(new, old, pos_new, pos_old);
		if (!envvar_step(new, old, pos_new, pos_old))
			return (0);
		new[*pos_new] = '"';
	}
	else
		new[*pos_new] = old[*pos_old];
	(*pos_old)++;
	(*pos_new)++;
	return (1);
}

/*
** Actually build a new string with the encapsulated envvars.
*/

static int		envvar_replace(char *newstr, char *oldstr)
{
	size_t	pos_old;
	size_t	pos_new;

	pos_old = 0;
	pos_new = 0;
	while (oldstr[pos_old] != '\0')
	{
		if (oldstr[pos_old] == '"')
		{
			char_copyover(newstr, oldstr, &pos_new, &pos_old);
			while (!(oldstr[pos_old] == '"' &&
				escapes_count(oldstr, pos_old) % 2 == 0))
			{
				if (inquotes(newstr, oldstr, &pos_new, &pos_old) == 0)
					return (0);
			}
			char_copyover(newstr, oldstr, &pos_new, &pos_old);
		}
		newstr[pos_new] = oldstr[pos_old];
		if (oldstr[pos_old] != '\0')
			pos_old++;
		pos_new++;
	}
	return (1);
}

/*
** This function will look for environment variables inside " quoted strings.
** We will encapsulate the envvars with " so the lexer will parse them like
** normal envvars.
*/

char			*envvar_fix_quoted(char *str)
{
	size_t	cnt;
	char	*newstr;
	int		res;

	if (str == NULL)
		return (NULL);
	cnt = envvars_quot_count(str);
	if (cnt == 0)
		return (str);
	newstr = ft_calloc(1, ft_strlen(str) + (cnt * 2) + 1);
	if (newstr == NULL)
		return (NULL);
	res = envvar_replace(newstr, str);
	free(str);
	if (res == 0)
	{
		free(newstr);
		return (NULL);
	}
	return (newstr);
}
