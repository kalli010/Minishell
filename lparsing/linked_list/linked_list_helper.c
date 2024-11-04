/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:07 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:08 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process_command_and_options(t_list **n_list, t_list **tmp, t_list *start,
		t_list **e)
{
	t_list	*end;

	end = NULL;
	if (*tmp && ((*tmp)->type == COMMAND || (*tmp)->type == OPTIONS))
	{
		start = *tmp;
		end = *tmp;
		while (*tmp && ((*tmp)->type == COMMAND || (*tmp)->type == OPTIONS))
		{
			if (ft_lstadd_back(n_list, ft_lstnew((*tmp)->content)))
			{
				free_list(*n_list);
				return (1);
			}
			// set_token_type(*n_list);
			*tmp = (*tmp)->next;
		}
		start->back->next = *tmp;
	}
	*e = end;
	return (0);
}

int	add_original_content(t_list **n_list, t_list *list)
{
	if (ft_lstadd_back(n_list, ft_lstnew(list->content)))
	{
		free_list(*n_list);
		return (1);
	}
	return (0);
}

void	free_processed_commands(t_list *end)
{
	t_list	*tmp;

	while (end)
	{
		tmp = end;
		end = end->next;
		free(tmp);
	}
}

int	collect_command_and_options(t_list *list, t_list **n_list, t_list *tmp,
		t_list *start)
{
	t_list	*end;

	end = NULL;
	find_command_end(list, &tmp);
	if (process_command_and_options(n_list, &tmp, start, &end))
		return (1);
	if (add_original_content(n_list, list))
		return (1);
	free(end);
  // free_processed_commands(end);
	return (0);
}

void	set_token_types(t_list *tmp, t_list *n_list, t_list **lst)
{
	tmp = n_list;
	while (tmp)
	{
		token_type(tmp);
		tmp = tmp->next;
	}
	*lst = n_list;
}
