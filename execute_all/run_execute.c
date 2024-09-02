/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 08:18:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	execute_parenthesis(t_tree *root, t_helper *helper)
{
	return (find_command(root->first_child, helper));
}

static int	check_root(t_tree *root, t_helper *helper)
{
	if (root->content->type == HEREDOC)
		return (here_doc(root, helper));
	if (root->content->type == AND || root->content->type == OR)
		return (check_and_or(root, helper));
	if (root->content->type == PIPE)
		return (execute_pipe(root, helper));
	return (EXIT_SUCCESS);
}

int	find_command(t_tree *root, t_helper *helper)
{
	if (!root)
		return (EXIT_FAILURE);
	if (root->first_child && root->first_child->content
		&& root->first_child->next_sibling
		&& root->first_child->next_sibling->content
		&& root->first_child->next_sibling->content->type != COMMAND)
		return (execute_parenthesis(root, helper));
	if ((root->content->type == COMMAND || root->content->type == PATH_COMMAND)
		&& (root->first_child == NULL || root->first_child->content == NULL
			|| root->first_child->content->type == OPTIONS))
	{
		if (is_builtins(root) == true)
			return (run_builtins(root, helper));
		else
			return (execute(root, helper));
	}
	if (root->content->type == OUTPUT || root->content->type == APPEND)
		return (redirect_output(root, helper));
	if (root->content->type == INPUT)
	{
		return (redirect_input(root, helper));
	}
	else
		return (check_root(root, helper));
}
