/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: JKCTech <admin@jkctech.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 15:22:54 by JKCTech       #+#    #+#                 */
/*   Updated: 2020/12/01 16:07:25 by JKCTech       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ui.h"
#include "messages.h"
#include <libft.h>

/*
** Create new string element and allocate properly.
** Optional with string.
*/

t_selem		*elem_new(t_token_type type, char *str)
{
	t_selem	*item;

	item = (t_selem*)malloc(sizeof(*item));
	if (item == NULL)
		return (NULL);
	ft_bzero(item, sizeof(t_selem));
	item->type = type;
	if (str != NULL)
	{
		item->str = ft_strdup(str);
		if (item->str == NULL)
		{
			free(item);
			item = NULL;
		}
	}
	return (item);
}

/*
** Append new string element to list of elements
*/

int			elem_append(t_selem **head, t_selem *new)
{
	t_selem	*item;

	if (head == NULL)
		return (0);
	if (*head == NULL)
		*head = new;
	else
	{
		item = *head;
		while (item->next != NULL)
			item = item->next;
		item->next = new;
	}
	return (1);
}

/*
** Iterates over the linked list and frees all elements.
*/

void		elems_free(t_selem **head)
{
	t_selem	*list;
	t_selem	*current;

	if (head == NULL || *head == NULL)
		return ;
	list = *head;
	while (list != NULL)
	{
		current = list;
		free(current->str);
		list = list->next;
		free(current);
	}
	*head = NULL;
}

/*
** Since we are not allowed by norm to make proper preprocessors....
** I have to build stuff like this...
*/

char		*elem_to_string(t_token_type type)
{
	if (type == SPACE)
		return (ft_strdup("SPACE"));
	else if (type == PIPE)
		return (ft_strdup("PIPE"));
	else if (type == STRING_LIT)
		return (ft_strdup("STRING_LIT"));
	else if (type == STRING_QOT)
		return (ft_strdup("STRING_QOT"));
	else if (type == STRING_RAW)
		return (ft_strdup("STRING_RAW"));
	else if (type == SEMICOLON)
		return (ft_strdup("SEMICOLON"));
	else if (type == LT)
		return (ft_strdup("LT"));
	else if (type == GT)
		return (ft_strdup("GT"));
	else if (type == GTGT)
		return (ft_strdup("GTGT"));
	else if (type == NONE)
		return (ft_strdup("NONE"));
	else if (type == ENVVAR)
		return (ft_strdup("ENVVAR"));
	else
		return (ft_strdup("UNKNOWN"));
}
