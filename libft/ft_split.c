/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 17:45:38 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/04 13:46:42 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t		ft_wordcnt(const char *str, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		while (str[i] != c && str[i] != '\0')
			i++;
		count++;
	}
	if (str[i - 1] == c)
		count--;
	return (count);
}

static size_t		ft_wordlen(const char *str, char c)
{
	size_t len;

	len = 0;
	while (*str != c && *str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

static char			**ft_cleanup(char **ptr, size_t count)
{
	size_t	i;

	if (ptr)
	{
		i = 0;
		while (i < count)
		{
			if (ptr[i] != NULL)
				free(ptr[i]);
			i++;
		}
		free(ptr);
	}
	return (NULL);
}

static char			**ft_copyover(char **output, const char *s, char c)
{
	size_t		j;
	size_t		k;

	j = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			continue ;
		output[j] = malloc(sizeof(char*) * ft_wordlen(s, c) + 1);
		if (output[j] == NULL)
			return (ft_cleanup(output, j));
		k = 0;
		while (*s != c && *s != '\0')
		{
			output[j][k] = *s;
			k++;
			s++;
		}
		output[j][k] = '\0';
		j++;
	}
	output[j] = NULL;
	return (output);
}

char				**ft_split(const char *s, char c)
{
	char	**output;

	if (s == NULL)
		return (NULL);
	output = malloc(sizeof(char*) * (ft_wordcnt(s, c) + 1));
	if (output == NULL)
		return (NULL);
	ft_copyover(output, s, c);
	return (output);
}
