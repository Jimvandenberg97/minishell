/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 10:25:56 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/10 14:49:28 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list		*list;

	if (lst == NULL)
		return ;
	list = lst;
	while (list != NULL)
	{
		f(list->content);
		list = list->next;
	}
	f(list->content);
}
