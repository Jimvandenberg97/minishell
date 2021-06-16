/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chars.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 17:01:14 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:07:17 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Indicate of the current character is a special operator
*/

int		is_operator(char c)
{
	if (ft_isspace(c) || c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

/*
** Count the amount of escapes backwards from the startpoint
** Also making sure we don't go past the starting pointer
*/

size_t	escapes_count(char *string, size_t start)
{
	size_t		count;
	size_t		pos;

	if (string == NULL)
		return (0);
	count = 0;
	pos = start - 1;
	while (string[pos - count] == '\\' && count <= pos)
		count++;
	return (count);
}
