/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 01:55:28 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/06/29 11:56:11 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static char		*ft_strdupx(const char *s1, int *res)
{
	char	*ptr;
	int		len;

	if (s1 == NULL)
		return (ft_strdupx("", res));
	len = ft_strlen(s1);
	ptr = malloc(len + 1);
	if (ptr == NULL)
	{
		*res = -1;
		return (NULL);
	}
	ft_memcpy(ptr, s1, len);
	ptr[len] = '\0';
	return (ptr);
}

static char		*ft_strchrx(const char *s, int c)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char*)s;
	while (*str != '\0')
		if (*str == c)
			return (str);
		else
			str++;
	if (c == '\0')
		return (str);
	return (NULL);
}

static char		*ft_strjoinx(char *s1, char *s2, int *res)
{
	char		*str;
	size_t		l1;
	size_t		l2;

	if (s1 == NULL || s2 == NULL)
	{
		*res = -1;
		return (NULL);
	}
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(l1 + l2 + 1);
	if (str == NULL)
	{
		*res = -1;
		return (NULL);
	}
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l1 + l2 + 1);
	return (str);
}

static int		ft_read(const int fd, char *fd_store[fd], int x)
{
	char	*buf;
	char	*tmp;
	int		tmp_res;

	buf = (char *)malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	tmp_res = read(fd, buf, GNL_BUFFER_SIZE);
	if (tmp_res >= 0 && x != -1)
		buf[tmp_res] = '\0';
	if (fd_store[fd] == NULL && tmp_res > 0 && x != -1)
		fd_store[fd] = ft_strdupx(buf, &tmp_res);
	else if (tmp_res > 0 && x != -1)
	{
		tmp = fd_store[fd];
		fd_store[fd] = ft_strjoinx(tmp, buf, &tmp_res);
		free(tmp);
	}
	free(buf);
	if ((tmp_res == -1 && fd_store[fd]) || (x == -1 && fd_store[fd]))
	{
		free(fd_store[fd]);
		fd_store[fd] = NULL;
	}
	return ((x == -1) ? -1 : tmp_res);
}

int				ft_get_next_line(int fd, char **line)
{
	static char	*fd_store[INT_MAX];
	char		*ptr_nl;
	char		*tmp;
	int			res;

	if (!line || GNL_BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (-1);
	res = 1;
	while (!ft_strchrx(fd_store[fd], '\n') && res > 0)
		res = ft_read(fd, fd_store, res);
	if (res < 0)
		return (-1);
	ptr_nl = ft_strchrx(fd_store[fd], '\n');
	if (ptr_nl != NULL)
	{
		*line = ft_substr(fd_store[fd], 0, ptr_nl - fd_store[fd]);
		tmp = fd_store[fd];
		fd_store[fd] = ft_strdupx(ptr_nl + 1, &res);
		free(tmp);
		return ((*line == NULL || res < 0) ? ft_read(fd, fd_store, -1) : 1);
	}
	*line = ft_strdupx(fd_store[fd], &res);
	free(fd_store[fd]);
	fd_store[fd] = NULL;
	return ((*line == NULL || res < 0) ? -1 : 0);
}
