/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:58 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 21:44:20 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_lst_null(t_list **tmp, t_list **list, t_list **n_list)
{
	*tmp = NULL;
	*list = NULL;
  *n_list = NULL;
}

int	recreate_linked_list(t_list *list, t_list **lst)
{
	t_list	*n_list;
	t_list	*tmp;
	t_list	*start;

	set_lst_null(&tmp, &start, &n_list);
	while (list)
	{
		if (list->type == INPUT || list->type == OUTPUT)
		{
			if (collect_command_and_options(list, &n_list, tmp, start))
				return (1);
		}
		else
		{
			if (ft_lstadd_back(&n_list, ft_lstnew(list->content)))
			{
				free_list(n_list);
				return (1);
			}
		}
		tmp = list;
    list = list->next;
		free(tmp);
	}
	set_token_types(tmp, n_list, lst);
	return (0);
}

void	clean_linked_list(t_list **list)
{
	t_list	*tmp;
	t_list	*back;
	t_list	*next;

	tmp = *list;
	while (tmp)
	{
		if (tmp->content[0] == '\0')
		{
      back = tmp->back;
      next = tmp->next;
      free(tmp->content);
      free(tmp);
			if (back == NULL)
				*list = next;
			else
				back->next = next;
			if (next != NULL)
				next->back = back;
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
}
void	clean_linked_list_par(t_list **list)
{
	t_list	*tmp;
	t_list	*back;
	t_list	*next;

	tmp = *list;
	while (tmp)
	{
		if (tmp->content[0] == 40 || tmp->content[0] == 41)
		{
			back = tmp->back;
			next = tmp->next;
			free(tmp->content);
			free(tmp);
			if (back == NULL)
				*list = next;
			else
				back->next = next;
			if (next != NULL)
				next->back = back;
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
}
