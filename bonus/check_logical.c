/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:33:17 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/29 10:17:47 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_and_or(t_tree *root, t_helper *helper)
{
	if (root->content->type == AND)
	{
		if (find_command(root->first_child, helper) == 0)
			return (find_command(root->first_child->next_sibling, helper));
	}
	else if (root->content->type == OR)
	{
		if (!find_command(root->first_child, helper))
			return (find_command(root->first_child->next_sibling, helper));
	}
	return (EXIT_SUCCESS);
}
