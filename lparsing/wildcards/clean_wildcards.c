/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:49:02 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:49:03 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wildcards_linked_list(t_list *list, char *str)
{
	t_list	*next;

	next = list->next;
	list->next = NULL;
	ft_lstadd_back(&list, ft_lstnew_2(str));
	list = list->next;
	list->type = OPTIONS;
	if (list && next)
	{
		list->next = next;
		next->back = list;
	}
}

void	clean_wildcards(t_list **list)
{
	t_list	*back;
	t_list	*next;

	back = (*list)->back;
	next = (*list)->next;
	next->type = COMMAND;
	free((*list)->content);
	free(*list);
	if (back)
	{
		back->next = next;
	}
	if (next)
	{
		next->back = back;
		if (back == NULL)
			*list = next;
		else
			*list = back;
	}
}
