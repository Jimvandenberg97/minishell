/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:28:55 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/04 13:46:59 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	pos;
	size_t	len;

	pos = ft_strlen(dst);
	len = ft_strlen(src);
	if (dstsize == 0)
		return (pos + len);
	if (dstsize < pos)
		len += dstsize;
	else
		len += pos;
	while (src != NULL && pos + 1 < dstsize)
	{
		dst[pos] = *src;
		pos++;
		src++;
	}
	dst[pos] = '\0';
	return (len);
}
