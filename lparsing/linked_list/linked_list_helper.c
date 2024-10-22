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

void	free_list(t_list *list)
{
	t_list	*tmp;

	if (list == NULL)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

int	creat_linked_list(t_list **list, char **tokens)
{
	int		i;
	t_list	*tmp;

	i = -1;
	while (tokens[++i])
	{
		if (ft_lstadd_back(list, ft_lstnew(tokens[i])))
		{
			free_list(*list);
			free(tokens);
			return (1);
		}
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		token_type(tmp);
	}
  free(tokens);
	return (0);
}

int	check_red_with_cmd(t_list *list)
{
	while (list)
	{
		if (list->type == INPUT || list->type == OUTPUT || list->type == APPEND)
		{
			if (list->next != NULL && list->next->next != NULL
				&& (list->next->next->type == COMMAND
					|| list->next->next->type == OPTIONS))
				return (1);
		}
		list = list->next;
	}
	return (0);
}

int	collect_command_and_options(t_list *list, t_list **n_list, t_list *tmp,
		t_list *start)
{
  t_list *end;

	tmp = list->next;
	while (tmp && (tmp->type == PATH || tmp->type == PATH_COMMAND
			|| tmp->type == INPUT || tmp->type == OUTPUT
			|| tmp->type == APPEND))
		tmp = tmp->next;
	if (tmp && (tmp->type == COMMAND || tmp->type == OPTIONS))
	{
		start = tmp;
    end = tmp;
		while (tmp && (tmp->type == COMMAND || tmp->type == OPTIONS))
		{
			if (ft_lstadd_back(n_list, ft_lstnew(tmp->content)))
			{
				free_list(*n_list);
				return (1);
			}
			token_type(*n_list);
			tmp = tmp->next;
		}
		start->back->next = tmp;
	}
	if (ft_lstadd_back(n_list, ft_lstnew(list->content)))
	{
		free_list(*n_list);
		return (1);
	}
  while(end)
  {
    tmp = end;
    end = end->next;
    free(tmp);
  }
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
