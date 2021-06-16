/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_strings.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 09:36:40 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/07 15:08:37 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"
#include <libft.h>

/*
** Strings determined by single quotes ('')
** Returns 0 or 1 on failure or success respectively
*/

static int	literalstring(t_lex_state *state)
{
	size_t		start;
	size_t		len;

	start = state->pos;
	state->pos++;
	len = 1;
	while (state->input[state->pos] != '\0')
	{
		if (state->input[state->pos] == '\'')
		{
			slice_prepare(state, start, len, STRING_LIT);
			return (1);
		}
		state->pos++;
		len++;
	}
	lex_error(state, "Unbalanced single quotes.");
	g_env->last_status = 2;
	return (0);
}

/*
** Strings determined by double quotes ("")
** Returns 0 or 1 on failure or success respectively
*/

static int	quotedstring(t_lex_state *state)
{
	size_t		start;
	size_t		len;

	start = state->pos;
	state->pos++;
	len = 1;
	while (state->input[state->pos] != '\0')
	{
		if (state->input[state->pos] == '"')
		{
			if (escapes_count(state->input, state->pos) % 2 == 0)
			{
				slice_prepare(state, start, len, STRING_QOT);
				return (1);
			}
		}
		state->pos++;
		len++;
	}
	lex_error(state, "Unbalanced double quotes.");
	g_env->last_status = 2;
	return (0);
}

/*
** Any other form of string
** Returns 0 or 1 on failure or success respectively
*/

static int	rawstring(t_lex_state *state)
{
	size_t		start;
	size_t		len;

	start = state->pos;
	state->pos++;
	len = 1;
	while (state->input[state->pos] != '\0' && state->input[state->pos] != '0')
	{
		if (is_operator(state->input[state->pos]) ||
			state->input[state->pos] == '$' || state->input[state->pos] == '"'
			|| state->input[state->pos] == '\'')
			break ;
		state->pos++;
		len++;
	}
	slice_prepare(state, start, len, STRING_RAW);
	state->pos--;
	return (1);
}

/*
** Select which type of string we're working with.
** Returns 0 or 1 on failure or success respectively
*/

int			lex_string(t_lex_state *state)
{
	if (state->input[state->pos] == '\'')
		return (literalstring(state));
	else if (state->input[state->pos] == '"')
		return (quotedstring(state));
	else
		return (rawstring(state));
}
