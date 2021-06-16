/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 15:09:07 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:09:06 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "lexer.h"

/*
** Init the lexer state with the current information we have + empty it first.
** I prefer to make another copy of the input.
** bzero() handles the setting of values to 0 and NULL.
*/

t_lex_state		*lex_state_init(char *input)
{
	t_lex_state *state;

	if (input == NULL)
		return (NULL);
	state = (t_lex_state*)malloc(sizeof(*state));
	if (state == NULL)
		return (0);
	ft_bzero(state, sizeof(t_lex_state));
	state->input = ft_strdup(input);
	if (state->input == NULL)
	{
		free(state);
		return (NULL);
	}
	state->slice_type = NONE;
	return (state);
}

/*
** Clear & reset the slice information from the lexer state.
*/

void			lex_state_clearslice(t_lex_state *state)
{
	if (state->slice != NULL)
	{
		free(state->slice);
		state->slice = NULL;
	}
	state->slice_type = NONE;
}

/*
** If an error is set, clear it
*/

void			lex_state_clearerror(t_lex_state *state)
{
	if (state->error != NULL)
	{
		free(state->error);
		state->error = NULL;
	}
}

/*
** Completely clear and free the lexer state for destruction.
*/

void			lex_state_free(t_lex_state *state)
{
	lex_state_clearerror(state);
	lex_state_clearslice(state);
	elems_free(&state->elements);
	free(state->input);
	free(state);
	state = NULL;
}
