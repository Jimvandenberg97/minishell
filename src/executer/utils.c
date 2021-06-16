/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 10:06:59 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/11/24 13:20:50 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "messages.h"
#include "ui.h"
#include <unistd.h>
#include <sys/stat.h>

int		ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		printerror(MSG_DUP, ERROR, 0);
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int		ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		printerror(MSG_PIPE, ERROR, 0);
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int		ft_dup(int fd)
{
	int	res;

	res = dup(fd);
	if (res == -1)
	{
		printerror(MSG_DUP, ERROR, 0);
		return (-1);
	}
	return (res);
}

int		fd_close(int fd)
{
	if (close(fd) == -1)
	{
		printerror(MSG_EXEC_FD_CLOSE, ERROR, 0);
		return (-1);
	}
	return (EXIT_SUCCESS);
}

void	exiterror(char *msg, t_errortype err, int stop, t_exec *exec)
{
	fd_closeall(exec);
	printerror(msg, err, stop);
}
