/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 16:01:51 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:55:14 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ui.h"
#include "messages.h"
#include <stdlib.h>

/*
** Loop over complete input, and select type of lexer per part.
*/

static int	selecter(t_lex_state *state)
{
	int		result;

	while (state->input[state->pos] != '\0')
	{
		if (is_operator(state->input[state->pos]))
			result = lex_operators(state);
		else if (state->input[state->pos] == '$')
			result = lex_envvar(state);
		else
			result = lex_string(state);
		if (result)
			slice_and_create(state);
		else if (state->input[state->pos] != '\0')
			lex_error(state, MSG_LEX_GENERIC);
		if (state->error != NULL)
			return (0);
		state->pos++;
	}
	return (1);
}

/*
** Where the fun begins, start the lexer :D
*/

t_lex_state	*lexer(char *input)
{
	t_lex_state *state;
	int			ret;

	input = envvar_fix_quoted(input);
	if (input == NULL)
	{
		printerror(MSG_LEX_QUOT, ERROR, 0);
		return (NULL);
	}
	state = lex_state_init(input);
	free(input);
	if (state == NULL)
	{
		printerror(MSG_LEX_INIT, ERROR, 0);
		return (NULL);
	}
	ret = selecter(state);
	if (state->error != NULL)
		printerror(state->error, ERROR, 0);
	if (ret == 0)
	{
		lex_state_free(state);
		state = NULL;
	}
	return (state);
}
