/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:17 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:50:18 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_n_node(t_tree **l_node, t_tree *root, t_tree **n_node)
{
	if ((*l_node)->content->type != COMMAND && root != *l_node)
		add_sibling_to_child(*l_node, *n_node);
	else
		add_child_to_tree(*l_node, *n_node);
}

t_tree	*or_and_tree(t_list **lst, t_tree **l_node, t_tree **root,
		t_tree **n_node)
{
	*l_node = creat_tree((*lst)->next);
	if (*l_node != NULL && ((*l_node)->content->type == OR
			|| (*l_node)->content->type == AND))
	{
		*root = *l_node;
		// if((*l_node)->first_child && (*l_node)->first_child->first_child->content)
		//   {
		//     while ((*l_node)->first_child->first_child->content->type != COMMAND)
		//       *l_node = (*l_node)->first_child;
		//   }
    add_child_to_tree(*n_node, (*l_node)->first_child);
    if((*l_node)->first_child)
    {
      add_sibling_to_child(*n_node, (*l_node)->first_child->next_sibling);
      (*l_node)->first_child->next_sibling = NULL;
    }
    (*l_node)->first_child = *n_node;
  }
	else
		add_child_to_tree(*n_node, *l_node);
	return (*root);
}

t_tree	*creat_tree(t_list *lst)
{
	t_tree	*root;
	t_tree	*n_node;
	t_tree	*l_node;

	set_to_null(&root, &n_node, &l_node);
	while (lst)
	{
		if (lst->content[0] == 41 || lst->content[0] == 40)
			return (root);
		n_node = create_tree_node(lst);
		if (root == NULL)
			root = n_node;
		else if (check_tmp(n_node->content))
		{
			add_child_to_tree(n_node, root);
			root = n_node;
		}
		else
			add_n_node(&l_node, root, &n_node);
		if (n_node->content->type == OR || n_node->content->type == AND)
			return (or_and_tree(&lst, &l_node, &root, &n_node));
		l_node = n_node;
		lst = lst->next;
	}
	return (root);
}
