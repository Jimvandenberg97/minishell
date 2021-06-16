/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_operators.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 13:22:23 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/30 15:23:04 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <libft.h>

/*
** Lexer detected an operator. Store the operator type as ENUM in the state.
*/

int			lex_operators(t_lex_state *state)
{
	if (ft_isspace(state->input[state->pos]))
	{
		state->slice_type = SPACE;
		while (ft_isspace(state->input[state->pos + 1]))
			state->pos++;
	}
	else if (state->input[state->pos] == '|')
		state->slice_type = PIPE;
	else if (state->input[state->pos] == '>')
		if (state->input[state->pos + 1] == '>')
		{
			state->slice_type = GTGT;
			state->pos++;
		}
		else
			state->slice_type = GT;
	else if (state->input[state->pos] == '<')
		state->slice_type = LT;
	else if (state->input[state->pos] == ';')
		state->slice_type = SEMICOLON;
	else
		return (0);
	return (1);
}

/*
** Validate first character inside an envvar
*/

static int	firstchar(t_lex_state *state, size_t *start, size_t *len)
{
	if (state->input[state->pos] == '?' || ft_isdigit(state->input[state->pos]))
	{
		slice_prepare(state, *start, 1, ENVVAR);
		return (1);
	}
	else if (ft_isalpha(state->input[state->pos]) ||
		state->input[state->pos] == '_')
	{
		(*len)++;
		state->pos++;
		return (0);
	}
	else
	{
		state->pos--;
		slice_prepare(state, (*start) - 1, 1, ENVVAR);
		return (1);
	}
}

/*
** Validate all other characters inside an envvar, and stop when done.
*/

static int	otherchars(t_lex_state *state, size_t *start, size_t *len)
{
	if (ft_isalnum(state->input[state->pos]) ||
		state->input[state->pos] == '_')
	{
		(*len)++;
		state->pos++;
		return (0);
	}
	else
	{
		state->pos--;
		slice_prepare(state, (*start), *len, ENVVAR);
		return (1);
	}
}

/*
** Lexer function that's dedicated to handling environment variables.
*/

int			lex_envvar(t_lex_state *state)
{
	size_t	start;
	size_t	len;

	start = state->pos + 1;
	state->pos++;
	if (state->input[state->pos] == '\0' ||
		ft_strchr(" /%", state->input[state->pos]))
	{
		state->pos--;
		slice_prepare(state, start - 1, 1, STRING_RAW);
		return (1);
	}
	len = 0;
	while (state->input[state->pos] != '\0')
	{
		if (len == 0 && firstchar(state, &start, &len) == 1)
			return (1);
		if (len != 0 && otherchars(state, &start, &len) == 1)
			return (1);
	}
	state->pos--;
	slice_prepare(state, start, len, ENVVAR);
	return (1);
}
