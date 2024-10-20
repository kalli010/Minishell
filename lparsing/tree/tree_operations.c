/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:58 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:58 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_l_tree(t_tree **l_tree, t_tree **r_tree, t_tree **s_tree)
{
	if (*l_tree != NULL)
	{
		if (*r_tree != NULL)
			add_child_to_tree(*r_tree, *l_tree);
		else
		{
			add_sibling_to_child(*l_tree, (*s_tree)->first_child);
			(*s_tree)->first_child = *l_tree;
		}
	}
}

void	add_s_tree(t_tree **r_tree, t_tree **s_tree)
{
	if (*r_tree == NULL)
		*r_tree = *s_tree;
	else if (*s_tree != NULL && (*s_tree)->first_child != NULL)
	{
		add_sibling_to_child(*r_tree, (*s_tree)->first_child);
		(*s_tree)->first_child = *r_tree;
		*r_tree = *s_tree;
	}
	else if (*s_tree != NULL && (*s_tree)->first_child == NULL)
	{
		add_child_to_tree(*s_tree, *r_tree);
		*r_tree = *s_tree;
	}
}

void	set_to_null(t_tree **s_tree, t_tree **r_tree, t_tree **l_tree)
{
	*l_tree = NULL;
	*s_tree = NULL;
	*r_tree = NULL;
}

t_tree	*creat_subtree(t_list **list)
{
	t_tree	*s_tree;
	t_tree	*r_tree;
	t_tree	*l_tree;

	set_to_null(&s_tree, &r_tree, &l_tree);
	while (*list && (*list)->content[0] != 41)
	{
		if ((*list)->content[0] == 40)
		{
			*list = (*list)->next;
			l_tree = creat_subtree(&(*list));
			*list = (*list)->next;
		}
		s_tree = creat_tree(*list);
		while ((*list)->content[0] != 41)
		{
			(*list)->in = 1;
			if ((*list)->content[0] == 40)
				break ;
			*list = (*list)->next;
		}
		add_l_tree(&l_tree, &r_tree, &s_tree);
		add_s_tree(&r_tree, &s_tree);
	}
	return (r_tree);
}

void	attach_node_to_tree(t_tree **l_node, t_list *list, t_tree **r_tree)
{
	t_tree	*tmp;
	t_tree	*tmp2;

	if ((*l_node)->first_child->content->type == COMMAND
		|| (*l_node)->content == list)
	{
		add_sibling_to_child(*r_tree, (*l_node)->first_child);
		(*l_node)->first_child = *r_tree;
	}
	else
	{
		tmp = (*l_node)->first_child;
		while (check_tmp(tmp->first_child->content))
			tmp = tmp->first_child;
		tmp2 = tmp->first_child;
		tmp->first_child = *r_tree;
		(*r_tree)->next_sibling = tmp2;
	}
}
