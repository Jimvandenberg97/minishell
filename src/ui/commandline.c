/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commandline.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 12:14:38 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:08:28 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include "ui.h"

static int	cleanup(char **readbuff)
{
	if (*readbuff != NULL)
	{
		free(*readbuff);
		*readbuff = NULL;
	}
	return (1);
}

static int	getline(char **readbuff)
{
	char	*tmp;
	char	buff[SIZE_READIN + 1];
	int		res;

	res = read(STDIN_FILENO, buff, SIZE_READIN);
	if (res < 0)
		return (-1);
	buff[res] = '\0';
	if (*readbuff == NULL)
		*readbuff = ft_strdup(buff);
	else
	{
		tmp = *readbuff;
		*readbuff = ft_strjoin(tmp, buff);
		free(tmp);
	}
	if (*readbuff == NULL)
		return (cleanup(readbuff));
	return (res);
}

/*
** Collects user input from stdin in a single string for easy parsing.
** Basically get_next_line but rewritten because mine was trash.
*/

int			inputcollector(char **line, int res)
{
	char		*tmp;
	char		*ptr;
	static char	*readbuff;

	if (read(STDIN_FILENO, NULL, 0) == -1)
		return (-1);
	if (readbuff == NULL)
		res = getline(&readbuff);
	while (!ft_strchr(readbuff, '\n') && res > 0)
		getline(&readbuff);
	if (res < 0)
		return (-1);
	ptr = ft_strchr(readbuff, '\n');
	if (ptr != NULL)
	{
		*ptr = '\0';
		*line = ft_strdup(readbuff);
		tmp = readbuff;
		readbuff = ft_strdup(ptr + 1);
		free(tmp);
		return (cleanup(&readbuff));
	}
	*line = ft_strdup(readbuff);
	cleanup(&readbuff);
	return ((!(*line)) ? -1 : 0);
}
