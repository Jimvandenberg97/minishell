/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slicer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 11:42:38 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:07:53 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "lexer.h"
#include "ui.h"
#include "messages.h"

/*
** Remove escape characters within quoted strings.
*/

static void	string_remove_escapes(t_lex_state *state, char *str)
{
	size_t	pos_copy;
	size_t	pos_str;
	char	*copy;

	copy = ft_strdup(str);
	if (copy == NULL)
	{
		lex_error(state, MSG_SLICE_ESC);
		return ;
	}
	pos_copy = 0;
	pos_str = 0;
	ft_bzero(str, ft_strlen(str));
	while (copy[pos_copy] != '\0')
	{
		if (copy[pos_copy] == '\\')
		{
			if (copy[pos_copy + 1] == '\\' || copy[pos_copy + 1] == '$')
				pos_copy++;
		}
		str[pos_str] = copy[pos_copy];
		pos_copy++;
		pos_str++;
	}
	free(copy);
}

/*
** Create new slice values
*/

void		slice_prepare(t_lex_state *state, size_t start, size_t len,
	t_token_type type)
{
	if (type == STRING_QOT && state->input[start] == '"')
	{
		start++;
		len--;
	}
	if (type == STRING_QOT && state->input[start + len] == '"')
		len--;
	if (type == STRING_LIT && state->input[start] == '\'')
	{
		start++;
		len--;
	}
	if (type == STRING_LIT && state->input[start + len] == '\'')
		len--;
	if (type == STRING_QOT || type == STRING_LIT)
		len++;
	state->slice_type = type;
	state->slice = ft_substr(state->input, start, len);
	if (state->slice == NULL)
	{
		printerror(MSG_SLICE_PREP, ERROR, 0);
		return ;
	}
	if (type == STRING_QOT)
		string_remove_escapes(state, state->slice);
}

/*
** Convert slice to proper element which we can store.
*/

void		slice_and_create(t_lex_state *state)
{
	t_selem *element;

	element = elem_new(state->slice_type, state->slice);
	if (element == NULL)
		lex_error(state, MSG_SLICE);
	if (elem_append(&state->elements, element) == 0)
		lex_error(state, MSG_LEX_APPEND);
	lex_state_clearslice(state);
}
