/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 15:39:31 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:08:21 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <unistd.h>
#include <libft.h>

static t_parser_command	*init_command(void)
{
	t_parser_command *command;

	command = ft_calloc(1, sizeof(t_parser_command));
	if (command == NULL)
		return (NULL);
	command->args = ft_calloc(1, sizeof(t_selem*));
	if (command == NULL)
	{
		free(command);
		return (NULL);
	}
	return (command);
}

static int				loop_append(t_parser_state *state)
{
	while (state->current_token != NULL &&
		state->current_token->type != SEMICOLON &&
		state->current_token->type != PIPE &&
		!token_isredirect(state->current_token))
	{
		if (state->current_token->type != SPACE)
		{
			state->current_command->args = cmd_append_arg(
				state->current_command->args, state->current_token);
			if (state->current_command->args == NULL)
			{
				free_command(state->current_command);
				return (0);
			}
			state->current_token = state->current_token->next;
			while (state->current_token && token_isstring(state->current_token))
			{
				state->current_token = state->current_token->next;
			}
		}
		else
			state->current_token = state->current_token->next;
	}
	return (1);
}

static int				alloc_redirects(t_parser_state *state)
{
	state->current_command->redirects_in = ft_calloc(1, sizeof(t_redirection*));
	if (state->current_command->redirects_in == NULL)
	{
		free_command(state->current_command);
		return (0);
	}
	state->current_command->redirects_out = ft_calloc(1,
		sizeof(t_redirection*));
	if (state->current_command->redirects_out == NULL)
	{
		free(state->current_command->redirects_in);
		free_command(state->current_command);
		return (0);
	}
	return (1);
}

static int				redirs(t_parser_state *state, t_redirection_type type)
{
	if (token_isredirect(state->current_token))
	{
		type = token_to_redirection(state->current_token->type);
		state->current_token = state->current_token->next;
		if (state->current_token == NULL)
			return (free_command(state->current_command));
		if (state->current_token->type == SPACE)
			state->current_token = state->current_token->next;
		if (state->current_token == NULL || !token_isstring(
			state->current_token))
			return (free_command(state->current_command));
		if (type == IN)
			state->current_command->redirects_in = cmd_append_redirect(
			state->current_command->redirects_in, state->current_token, type);
		else
			state->current_command->redirects_out = cmd_append_redirect(
			state->current_command->redirects_out, state->current_token, type);
		if (state->current_token != NULL)
			state->current_token = state->current_token->next;
	}
	return (1);
}

int						handle_pipes(t_parser_state *state)
{
	state->current_command = init_command();
	if (state->current_command == NULL)
		return (0);
	if (loop_append(state) == 0)
		return (0);
	if (alloc_redirects(state) == 0)
		return (0);
	while (state->current_token != NULL && (
			token_isredirect(state->current_token) ||
			state->current_token->type == SPACE ||
			token_isstring(state->current_token)))
	{
		if (redirs(state, IN) == 0 || loop_append(state) == 0)
			return (0);
		if (state->current_token != NULL &&
			token_isstring(state->current_token))
			state->current_token = state->current_token->next;
	}
	return (1);
}
