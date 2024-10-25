/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_with_parnethesis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:26 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:50:30 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	if_root_null(t_tree **r_tree, t_tree **l_node, t_list *list,
		t_tree **root)
{
	if (*r_tree != NULL)
	{
		if (*l_node != NULL && (*l_node)->first_child != NULL)
			attach_node_to_tree(l_node, list, r_tree);
		else if (*l_node != NULL)
			add_child_to_tree(*l_node, *r_tree);
	}
	if (*l_node != NULL)
		*root = *l_node;
	else
		*root = *r_tree;
}

void	manage_tree_with_pr(t_list **list, t_tree **r_tree, t_tree **root,
		t_tree **l_node)
{
	if (*root != NULL && *r_tree != NULL)
	{
		if ((*root)->first_child->next_sibling != NULL)
			add_child_to_tree((*root)->first_child->next_sibling, *r_tree);
		else
			add_child_to_tree(*root, *r_tree);
	}
	*l_node = creat_tree(*list);
	if (*root == NULL)
		if_root_null(r_tree, l_node, *list, root);
	else if (*l_node != NULL && (*l_node)->first_child != NULL)
	{
		add_sibling_to_child(*root, (*l_node)->first_child);
		(*l_node)->first_child = *root;
		*root = *l_node;
	}
	else if (*l_node != NULL && (*l_node)->first_child == NULL)
	{
		add_child_to_tree(*l_node, *root);
		*root = *l_node;
	}
}

t_tree	*creat_tree_with_parenthesis(t_list *list)
{
	t_tree	*root;
	t_tree	*l_node;
	t_tree	*r_tree;

	r_tree = NULL;
	l_node = NULL;
	root = NULL;
	while (list)
	{
		if (list->content[0] == 41)
			list = list->next;
		if (list->content[0] == 40)
		{
			list = list->next;
			r_tree = creat_subtree(&list);
			list = list->next;
		}
		manage_tree_with_pr(&list, &r_tree, &root, &l_node);
		while (list != NULL && list->content[0] != 40)
			list = list->next;
		r_tree = NULL;
	}
	if (root == NULL)
		root = r_tree;
	return (root);
}
