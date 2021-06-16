/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 15:07:10 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:55:57 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# define CLR_RST	"\x1B[0m"
# define CLR_RED	"\x1B[31m"
# define CLR_GRN	"\x1B[32m"
# define CLR_YLW	"\x1B[33m"
# define CLR_BLUE	"\x1B[34m"
# define CLR_MGNT	"\x1B[35m"
# define CLR_CYAN	"\x1B[36m"
# define CLR_WHTE	"\x1B[37m"

# define SIZE_READIN 128

# include "environment.h"

typedef enum	e_errortype {
	INFO,
	WARNING,
	ERROR
}				t_errortype;

void	printprefix(t_env *env);
void	printerror(char *msg, t_errortype err, int stop);
void	printerror_prefix(t_errortype err);
int		inputcollector(char **line, int res);

#endif
