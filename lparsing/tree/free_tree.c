/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:48 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:49 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tree(t_tree *root)
{
	t_tree	*child;
	t_tree	*next;

	if (root == NULL)
		return ;
	child = root->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_tree(child);
		child = next;
	}
	if (root->content->content != NULL)
		free(root->content->content);
	free(root->content);
	free(root);
}
