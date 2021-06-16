/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 15:44:06 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:06:32 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libft.h>
#include <unistd.h>
#include "ui.h"

/*
** Standard function for error on signal error
*/

static void	sig_stop(void)
{
	write(1, "Signal handler error\n", 21);
	exit(EXIT_FAILURE);
}

/*
** Interactive signals will behave differently than fork signals.
** Here we will only catch the interrupt and reprint the prefix.
*/

static void	signals_interactive(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		printprefix(g_env);
	}
}

/*
** In forked elements, we catch both SIGINT and SIGQUIT
** On SIGINT, again we print the prefix
*/

static void	signals_fork(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (signo == SIGQUIT)
	{
		write(1, "Quit\n", 5);
	}
}

void		signals_init_interactive(void)
{
	if (signal(SIGINT, signals_interactive) == SIG_ERR)
		sig_stop();
	if (signal(SIGQUIT, signals_interactive) == SIG_ERR)
		sig_stop();
}

void		signals_init_fork(void)
{
	if (signal(SIGINT, signals_fork) == SIG_ERR)
		sig_stop();
	if (signal(SIGQUIT, signals_fork) == SIG_ERR)
		sig_stop();
}
