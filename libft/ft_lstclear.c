/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 19:00:57 by jkoopman      #+#    #+#                 */
/*   Updated: 2020/07/07 12:37:09 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list		*list;
	t_list		*new;

	if (lst == NULL || *lst == NULL)
		return ;
	list = *lst;
	while (list != NULL)
	{
		new = list;
		list = list->next;
		del(new->content);
		free(new);
	}
	*lst = NULL;
}
