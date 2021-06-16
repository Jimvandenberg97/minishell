/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/24 14:36:37 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/30 15:14:20 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int					token_isredirect(t_selem *token)
{
	if (token == NULL)
		return (0);
	return (token->type == LT || token->type == GT || token->type == GTGT);
}

int					token_isstring(t_selem *token)
{
	return (token->type == STRING_LIT || token->type == STRING_QOT ||
		token->type == STRING_RAW || token->type == ENVVAR);
}

t_redirection_type	token_to_redirection(t_token_type type)
{
	if (type == LT)
		return (IN);
	else if (type == GT)
		return (TRUNCATE);
	else
		return (APPEND);
}

size_t				layer_count(t_parser_state *state)
{
	t_cmdlist			*layer;
	t_partlist			*list;
	size_t				cnt;

	layer = state->result;
	cnt = 0;
	while (layer != NULL)
	{
		list = layer->list;
		while (list != NULL)
		{
			cnt++;
			list = list->next;
		}
		layer = layer->next;
	}
	return (cnt);
}
