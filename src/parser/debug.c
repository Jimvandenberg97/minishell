/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 15:19:55 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:00:58 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>

static void	loop(t_parser_command *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		ft_printf("\t\tARG: [%d] %s\n", cmd->args[i]->type, cmd->args[i]->str);
		i++;
	}
	i = 0;
	while (cmd->redirects_in[i] != NULL)
	{
		ft_printf("\t\tREDIRECT IN: [%d] %s\n", cmd->redirects_in[i]->type,
			cmd->redirects_in[i]->file->str);
		i++;
	}
	i = 0;
	while (cmd->redirects_out[i] != NULL)
	{
		ft_printf("\t\tREDIRECT OUT: [%d] %s\n", cmd->redirects_out[i]->type,
			cmd->redirects_out[i]->file->str);
		i++;
	}
}

void		parser_debug(t_parser_state *state)
{
	t_cmdlist			*layer;
	t_partlist			*list;
	t_parser_command	*cmd;

	if (state == NULL)
		return ;
	layer = state->result;
	while (layer != NULL)
	{
		ft_printf("Commands\n");
		list = layer->list;
		while (list != NULL)
		{
			ft_printf("\tELEMENT\n");
			cmd = list->command;
			loop(cmd);
			list = list->next;
		}
		layer = layer->next;
	}
}
