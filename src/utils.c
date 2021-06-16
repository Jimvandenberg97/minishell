/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 10:52:01 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 12:26:45 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "environment.h"
#include "ui.h"
#include <libft.h>

void	lexer_check(t_lex_state *state_lex)
{
	t_selem		*current;
	size_t		cnt;

	current = state_lex->elements;
	cnt = 0;
	while (current != NULL)
	{
		if (current->type == PIPE && cnt == 0)
			lex_error(state_lex, "Unexpected pipe.");
		else if (token_isstring(current) || current->type == ENVVAR)
			cnt++;
		else if (current->type == SEMICOLON || current->type == PIPE)
			cnt = 0;
		current = current->next;
	}
}

void	lexer_debug(t_lex_state *state_lex)
{
	char			*str;
	t_selem			*current;

	if (g_env->debug)
	{
		printerror("START LEXER", INFO, 0);
		ft_printf("Input: %s\n", state_lex->input);
		ft_printf("--- ELEMENTS ---\n");
		current = state_lex->elements;
		while (current != NULL)
		{
			str = elem_to_string(current->type);
			ft_printf("[%s]: |%s|\n", str, current->str);
			free(str);
			current = current->next;
		}
		ft_printf("--- END ELEMENTS ---\n");
		printerror("END LEXER", INFO, 0);
		ft_printf("\n");
	}
}

int		shell_close(void)
{
	int ret;

	write(STDERR_FILENO, "exit\n", 5);
	ret = g_env->last_status;
	env_free(g_env);
	return (ret);
}
