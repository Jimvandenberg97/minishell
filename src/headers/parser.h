/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 11:20:20 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:58:45 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include "lexer.h"
# include "environment.h"

typedef enum			e_redirection_type {
	IN,
	TRUNCATE,
	APPEND
}						t_redirection_type;

typedef struct			s_redirection {
	t_selem				*file;
	t_redirection_type	type;
}						t_redirection;

typedef struct			s_parser_command {
	t_selem				**args;
	t_redirection		**redirects_in;
	t_redirection		**redirects_out;
}						t_parser_command;

/*
** Linked list of elements seperated by '|' inside an element seperated by ';'.
*/

typedef struct			s_partlist {
	t_parser_command	*command;
	struct s_partlist	*next;
}						t_partlist;

/*
** Linked list of elements seperated by ';' from the input string.
*/

typedef struct			s_cmdlist {
	t_partlist			*list;
	struct s_cmdlist	*next;
}						t_cmdlist;

typedef struct			s_parser_state {
	char				*error;
	t_selem				*current_token;
	t_parser_command	*current_command;
	t_cmdlist			*result;
}						t_parser_state;

/*
** Parser
*/

t_parser_state			*parser(t_lex_state *lex, t_env *env);
int						handle_tokens(t_parser_state *state);
int						command_add(t_parser_state *state);

/*
** Args
*/

t_selem					**cmd_append_arg(t_selem **args, t_selem *token);
t_redirection			**cmd_append_redirect(t_redirection **redirects,
							t_selem *token, t_redirection_type type);
size_t					argv_count(t_selem **args);
int						handle_pipes(t_parser_state *state);

/*
** Utils
*/

int						token_isredirect(t_selem *token);
int						token_isstring(t_selem *token);
t_redirection_type		token_to_redirection(t_token_type type);
size_t					layer_count(t_parser_state *state);
void					parser_debug(t_parser_state *state);

/*
** Frees
*/

void					free_args(t_selem **args);
int						free_command(t_parser_command *command);
void					parser_free(t_parser_state *parser);

#endif
