/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 10:13:56 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 15:55:53 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include <libft.h>
#include <unistd.h>

static void	printbox(char *str, char *clr1, char *clr2)
{
	write(STDERR_FILENO, clr1, ft_strlen(clr1));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, clr2, ft_strlen(clr2));
	write(STDERR_FILENO, ": ", 2);
}

void		printerror_prefix(t_errortype err)
{
	if (err == INFO)
		printbox("[INFO]", CLR_CYAN, CLR_RST);
	else if (err == WARNING)
		printbox("[WARNING]", CLR_YLW, CLR_RST);
	else if (err == ERROR)
		printbox("[ERROR]", CLR_RED, CLR_RST);
}

void		printerror(char *msg, t_errortype err, int stop)
{
	printerror_prefix(err);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	if (stop != 0)
		exit(stop);
}
