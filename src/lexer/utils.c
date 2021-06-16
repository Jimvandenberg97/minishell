/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 12:36:15 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:54:27 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "lexer.h"
#include "ui.h"
#include "messages.h"

/*
** Allocate for lexer errors.
** If there's already an error stored, pass.
*/

void	lex_error(t_lex_state *state, char *msg)
{
	if (state->error != NULL)
		return ;
	state->error = ft_strdup(msg);
	if (state->error == NULL)
	{
		printerror(MSG_LEX_ERR_ALLOC, ERROR, 0);
		return ;
	}
}
