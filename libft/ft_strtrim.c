/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 15:54:43 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/06/29 11:58:51 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int				inset(char c, const char *set)
{
	size_t		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static const char		*getstart(const char *s, const char *set)
{
	size_t		i;

	i = 0;
	while (inset(s[i], set) && s[i] != '\0')
		i++;
	return (&s[i]);
}

static const char		*getend(const char *s, const char *set)
{
	size_t		i;

	i = ft_strlen(s);
	if (i == 0)
		return (s);
	i--;
	while (inset(s[i], set) && i > 0)
		i--;
	return (&s[i]);
}

char					*ft_strtrim(const char *s1, const char *set)
{
	char		*str;
	size_t		len;
	size_t		i;
	char		*start;
	char		*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = (char*)getstart(s1, set);
	end = (char*)getend(s1, set);
	len = end - start + 1;
	if (end < start)
		len = 1;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
