/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/24 15:54:34 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:08:11 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

int			free_command(t_parser_command *command)
{
	size_t	i;

	free(command->args);
	i = 0;
	while (command->redirects_in[i] != NULL)
	{
		free(command->redirects_in[i]);
		i++;
	}
	i = 0;
	while (command->redirects_out[i] != NULL)
	{
		free(command->redirects_out[i]);
		i++;
	}
	free(command->redirects_in);
	free(command->redirects_out);
	free(command);
	return (0);
}

t_cmdlist	*command_layer_add(t_parser_state *state)
{
	t_cmdlist	*layer;

	layer = state->result;
	if (layer != NULL)
	{
		while (layer->next != NULL)
			layer = layer->next;
		layer->next = ft_calloc(1, sizeof(t_cmdlist));
		if (layer->next == NULL)
			return (NULL);
		return (layer->next);
	}
	else
	{
		state->result = ft_calloc(1, sizeof(t_cmdlist));
		if (state->result == NULL)
			return (NULL);
		return (state->result);
	}
}

static int	command_move(t_parser_state *state, t_cmdlist *layer,
				t_partlist *list)
{
	list = layer->list;
	if (list != NULL)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = ft_calloc(1, sizeof(t_partlist));
		if (list->next == NULL)
			return (0);
		list = list->next;
	}
	else
	{
		layer->list = ft_calloc(1, sizeof(t_partlist));
		if (layer->list == NULL)
			return (0);
		list = layer->list;
	}
	list->command = state->current_command;
	return (1);
}

int			command_add(t_parser_state *state)
{
	t_cmdlist	*layer;
	t_partlist	*list;

	layer = state->result;
	if (layer != NULL)
	{
		while (layer->next != NULL)
			layer = layer->next;
	}
	else
	{
		layer = command_layer_add(state);
		if (layer == NULL)
			return (0);
	}
	list = NULL;
	if (command_move(state, layer, list) == 0)
		return (0);
	if (state->current_token != NULL && state->current_token->type == SEMICOLON)
	{
		layer = command_layer_add(state);
		if (layer == NULL)
			return (0);
	}
	return (1);
}
