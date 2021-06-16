/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:20:10 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:08:17 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "environment.h"
#include "ui.h"
#include "messages.h"
#include <libft.h>

static t_parser_state	*init_parser(void)
{
	t_parser_state		*state;

	state = ft_calloc(1, sizeof(t_parser_state));
	if (state == NULL)
		return (NULL);
	return (state);
}

void					parser_free(t_parser_state *parser)
{
	t_cmdlist			*layer;
	t_cmdlist			*tmp_layer;
	t_partlist			*list;
	t_partlist			*tmp_list;
	t_parser_command	*cmd;

	layer = parser->result;
	while (layer != NULL)
	{
		list = layer->list;
		while (list != NULL)
		{
			cmd = list->command;
			free_command(cmd);
			tmp_list = list->next;
			free(list);
			list = tmp_list;
		}
		tmp_layer = layer->next;
		free(layer);
		layer = tmp_layer;
	}
	if (parser->error != NULL)
		free(parser->error);
	free(parser);
}

static int				parser_loop(t_parser_state *state)
{
	while (state->current_token != NULL &&
		state->current_token->type != SEMICOLON)
	{
		if (!handle_pipes(state) || !command_add(state))
		{
			parser_free(state);
			printerror(MSG_PARSE_ERR, ERROR, 0);
			return (0);
		}
		if (state->current_token != NULL)
			state->current_token = state->current_token->next;
	}
	return (1);
}

t_parser_state			*parser(t_lex_state *lex, t_env *env)
{
	t_parser_state *state;

	state = init_parser();
	if (state == NULL)
		return (NULL);
	state->current_token = lex->elements;
	while (state->current_token != NULL)
	{
		if (parser_loop(state) == 0)
			return (NULL);
	}
	if (env->debug)
		parser_debug(state);
	return (state);
}
