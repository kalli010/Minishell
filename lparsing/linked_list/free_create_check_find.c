/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_create_check_find.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:08:48 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/04 23:17:05 by zelkalai         ###   ########.fr       */
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
		if (list->type == INPUT || list->type == OUTPUT \
				|| list->type == APPEND || list->type == HEREDOC)
		{
			if (list->next != NULL && list->next->next != NULL \
					&& (list->next->next->type == COMMAND \
						|| list->next->next->type == OPTIONS))
				return (1);
		}
		list = list->next;
	}
	return (0);
}

void	find_command_end(t_list *list, t_list **tmp)
{
	*tmp = list->next;
	while (*tmp && ((*tmp)->type == PATH || (*tmp)->type == PATH_COMMAND \
				|| (*tmp)->type == INPUT || (*tmp)->type == OUTPUT \
				|| (*tmp)->type == APPEND || (*tmp)->type == DELIMITER))
		*tmp = (*tmp)->next;
}
