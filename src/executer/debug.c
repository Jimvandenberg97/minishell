/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 13:12:30 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:00:01 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "executer.h"

void		exec_debug(t_exec *exec)
{
	size_t i;

	i = 0;
	ft_printf("REDIRECTIONS: [%d][%d]\n", exec->redir_in, exec->redir_out);
	ft_printf("PIPES PREV: [%d][%d]\n", exec->pipe_prev[0], exec->pipe_prev[1]);
	ft_printf("PIPES NEXT: [%d][%d]\n", exec->pipe_next[0], exec->pipe_next[1]);
	while (exec->args[i] != NULL)
	{
		ft_printf("- |%s|\n", exec->args[i]);
		i++;
	}
	ft_printf("---\n");
}
