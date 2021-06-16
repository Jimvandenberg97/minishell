/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:25:30 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/04 13:43:13 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	a = (unsigned char*)dst;
	b = (const unsigned char*)src;
	while (i < n)
	{
		a[i] = b[i];
		if (b[i] == (const unsigned char)c)
		{
			i++;
			return (dst + i);
		}
		i++;
	}
	return (NULL);
}
