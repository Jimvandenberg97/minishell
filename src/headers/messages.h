/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 09:10:18 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:53:32 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define MSG_NOT_FOUND "Command not found: "
# define MSG_EXECVE "Execution error: "
# define MSG_FORK "Forking error."
# define MSG_DUP "Failed duplicating filedescriptor."
# define MSG_PIPE "Failed to create pipeline."
# define MSG_MEMORY "Could not allocate internal memory."
# define MSG_IMPOSSIBLE "Impossible state, something went wrong."
# define MSG_TOO_MANY_ARGS "Too many arguments."
# define MSG_PREFIX "Could not print prefix"

# define MSG_CHDIR_PWD "Could not set $PWD in environment."
# define MSG_CD_NULL "Empty cd not supported."
# define MSG_PWD_FAIL "Cannot get PWD."
# define MSG_EXIT_INVALID "Invalid exitcode."

# define MSG_LEX_GENERIC "Error during lexing."
# define MSG_LEX_INIT "Could not initiate lexer."
# define MSG_LEX_ERR_ALLOC "Could not allocate error message."
# define MSG_LEX_QUOT "Could not preprocess command."
# define MSG_LEX_APPEND "Could not define command token."

# define MSG_SLICE_ESC "Error during removing escapes."
# define MSG_SLICE_PREP "Could not prepare slice."
# define MSG_SLICE "Could not slice."

# define MSG_PARSE_ERR "Error during parsing."

# define MSG_EXEC_FD_IN "Could not open input file."
# define MSG_EXEC_FD_OUT "Could not open output file."
# define MSG_EXEC_FD_CLOSE "Could not close filedescriptors properly."

# define MSG_REDIR "Redirection error."

#endif
