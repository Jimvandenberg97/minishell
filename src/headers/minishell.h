/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 11:05:38 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/08 12:20:56 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

void	lexer_debug(t_lex_state *state_lex);
int		shell_close(void);
void	lexer_check(t_lex_state *state_lex);

#endif
