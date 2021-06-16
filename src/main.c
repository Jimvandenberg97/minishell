/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 15:38:45 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 14:03:30 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "lexer.h"
#include "parser.h"
#include "executer.h"
#include "environment.h"
#include "ui.h"
#include "messages.h"
#include "minishell.h"

t_env	*g_env;

static void	shell_init(int argc, char *argv[], char *envp[])
{
	int	i;

	g_env = env_init(envp);
	g_env->argc = argc;
	g_env->argv = argv;
	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--debug") == 0)
			g_env->debug = 1;
		i++;
	}
	if (g_env->debug)
		printerror("DEBUGGING MODE ENABLED!", INFO, 0);
}

static int	getcommand(char **cmd, int *ret)
{
	signals_init_interactive();
	printprefix(g_env);
	*ret = inputcollector(cmd, 1);
	if (cmd == NULL)
	{
		printerror(MSG_MEMORY, ERROR, EXIT_FAILURE);
		return (0);
	}
	return (1);
}

static int	lexer_run(char *cmd, t_lex_state **state_lex, t_env *env)
{
	*state_lex = lexer(cmd);
	if (*state_lex == NULL)
	{
		if (g_env->last_status == 0)
			g_env->last_status = 1;
		printerror(MSG_LEX_GENERIC, ERROR, 0);
		env->last_status = 2;
		return (0);
	}
	lexer_check(*state_lex);
	if ((*state_lex)->error != NULL)
	{
		printerror((*state_lex)->error, ERROR, 0);
		lex_state_free(*state_lex);
		env->last_status = 2;
		return (0);
	}
	lexer_debug(*state_lex);
	return (1);
}

static int	parser_run(t_parser_state **state_parser, t_lex_state *state_lex)
{
	if (g_env->debug)
		printerror("START PARSER", INFO, 0);
	*state_parser = parser(state_lex, g_env);
	if (g_env->debug)
		printerror("END PARSER", INFO, 0);
	if (*state_parser == NULL)
	{
		printerror(MSG_PARSE_ERR, ERROR, 0);
		lex_state_free(state_lex);
		g_env->last_status = 2;
		return (0);
	}
	return (1);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_lex_state		*state_lex;
	t_parser_state	*state_parser;
	char			*cmd;
	int				ret;

	shell_init(argc, argv, envp);
	ret = 1;
	while (ret == 1)
	{
		cmd = NULL;
		if (getcommand(&cmd, &ret) == 0)
			continue;
		state_lex = NULL;
		if (lexer_run(cmd, &state_lex, g_env) == 0)
			continue;
		state_parser = NULL;
		if (parser_run(&state_parser, state_lex) == 0)
			continue;
		executer(state_parser, g_env);
		lex_state_free(state_lex);
		parser_free(state_parser);
	}
	ret = g_env->last_status;
	shell_close();
	return (ret % 256);
}
