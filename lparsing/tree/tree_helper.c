/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:55 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:51:56 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_tmp(t_list *tmp)
{
	return (tmp->type == PIPE || tmp->type == OR || tmp->type == AND
		|| tmp->type == OUTPUT || tmp->type == INPUT || tmp->type == HEREDOC
		|| tmp->type == APPEND);
}

t_tree	*create_tree_node(t_list *list)
{
	t_tree	*n_node;

	n_node = (t_tree *)malloc(sizeof(t_tree));
	if (!n_node)
		return (NULL);
	n_node->content = list;
	n_node->first_child = NULL;
	n_node->next_sibling = NULL;
	return (n_node);
}

void	add_child_to_tree(t_tree *parent, t_tree *child)
{
	t_tree	*last_sibling;

	if (parent == NULL)
		return ;
	if (parent->first_child == NULL)
		parent->first_child = child;
	else
	{
		last_sibling = parent->first_child;
		while (last_sibling->next_sibling != NULL)
			last_sibling = last_sibling->next_sibling;
		last_sibling->next_sibling = child;
	}
}

void	add_sibling_to_child(t_tree *child, t_tree *sibling)
{
	t_tree	*l_sibling;

	if (child->next_sibling == NULL)
		child->next_sibling = sibling;
	else
	{
		l_sibling = child->next_sibling;
		while (l_sibling->next_sibling != NULL)
			l_sibling = l_sibling->next_sibling;
		l_sibling->next_sibling = sibling;
	}
}

int	check_parenthesis(t_list *list)
{
	int	c;

	c = 0;
	while (list)
	{
		if (list->content != NULL && (list->content[0] == 40 || list->content[0] == 41))
		{
			c++;
			return (c);
		}
		list = list->next;
	}
	return (0);
}
