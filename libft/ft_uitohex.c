/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitohex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 16:06:52 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/06/29 11:58:51 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char				*ft_uitohex(unsigned int n)
{
	char		*str;
	size_t		i;

	i = ft_getnumlen(n, 16);
	str = (char*)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i--;
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i] = CHARSET_BASE[(n % 16)];
		n /= 16;
		i--;
	}
	return (str);
}
