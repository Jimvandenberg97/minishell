/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 14:18:25 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:58:16 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>

/*
** SPACE		' '
** PIPE			|
** STRING_LIT	''
** STRING_QOT	""
** STRING_RAW
** SEMICOLON	;
** LT			<		Less Than
** GT			>		Greater Than
** GTGT			>>		Greater Than Greater Than
** ENVVAR		$VAR	Environment Variable
** NONE					Default type
*/
typedef enum	e_token_type {
	SPACE,
	PIPE,
	STRING_LIT,
	STRING_QOT,
	STRING_RAW,
	SEMICOLON,
	LT,
	GT,
	GTGT,
	ENVVAR,
	NONE
}				t_token_type;

/*
** Linked list of command string elements.
** Every element consists of a type, and a string that goes with it.
*/

typedef struct			s_selem {
	t_token_type		type;
	char				*str;
	struct s_selem		*next;
}						t_selem;

/*
** State the lexer is in right now.
** This is sent to the parser later on.
*/

typedef struct			s_lex_state {
	char				*error;
	char				*input;
	char				*slice;
	t_token_type		slice_type;
	size_t				pos;
	t_selem				*elements;
}						t_lex_state;

/*
** Element functions
*/

t_selem					*elem_new(t_token_type type, char *str);
int						elem_append(t_selem **head, t_selem *new);
void					elems_free(t_selem **head);
void					slice_and_create(t_lex_state *state);
void					slice_prepare(t_lex_state *state, size_t start,
							size_t len, t_token_type type);
char					*elem_to_string(t_token_type type);

/*
** State functions
*/

t_lex_state				*lex_state_init(char *input);
void					lex_state_clearslice(t_lex_state *state);
void					lex_state_clearerror(t_lex_state *state);
void					lex_state_free(t_lex_state *state);

/*
** Lexing utilities
*/

int						is_operator(char c);
size_t					escapes_count(char *string, size_t start);
char					*envvar_fix_quoted(char *str);
int						envvar_step(char *new, char *old, size_t *pos_new,
							size_t *pos_old);

/*
** Lexing functions
*/

t_lex_state				*lexer(char	*input);
int						lex_string(t_lex_state *state);
int						lex_operators(t_lex_state *state);
int						lex_envvar(t_lex_state *state);

/*
** Utilities
*/

void					lex_error(t_lex_state *state, char *msg);

#endif
