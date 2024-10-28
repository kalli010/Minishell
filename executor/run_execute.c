/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/28 01:39:52 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_root_content(t_tree *root)
{
	if (root->content->content == NULL)
		return (0);
	if (!ft_strncmp(root->content->content, ".", sizeof(".")))
	{
		printf("minishell : .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		return (2);
	}
	if (!ft_strncmp(root->content->content, "!", sizeof("!")))
		return (1);
	if (!ft_strncmp(root->content->content, "..", sizeof("..")))
	{
		printf("..: command not found\n");
		return (127);
	}
	if (!ft_strncmp(root->content->content, "//", 1) && is_only_slashes(root))
	{
		printf("minishell: %s: Is a directory\n", root->content->content);
		return (126);
	}
	if (is_only_bs(root))
		return (127);
	return (0);
}

int	handle_redirection_and_pipes(t_tree *root, t_helper *helper, t_tree **rt)
{
	if (root->content->type == PIPE)
	{
		return (execute_pipe(root, helper, rt));
	}
	if (root->content->type == APPEND || root->content->type == OUTPUT
		|| root->content->type == INPUT)
	{
		if (redirect_all(root, helper, rt) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	find_command(t_tree *root, t_helper *helper, t_tree **rt)
{
	int status;
	
	if (!root)
		return (EXIT_SUCCESS);
	status = check_root_content(root);
	if (status)
	{
		g_helper.exit_status = status;
		return (g_helper.exit_status);
	}
	if (root->content->in == 1)
	{
		root->content->in = 0;
		return (execute_parenthesis(root, helper, rt));
	}
	if (root->content->type == AND || root->content->type == OR)
		return (check_and_or(root, helper, rt));
	if (handle_redirection_and_pipes(root, helper, rt))
		return (EXIT_FAILURE);
	if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
	{
		if (is_builtins(root) == true)
			return (run_builtins(root, helper));
		return (execute(root, helper, rt));
	}
	return (EXIT_SUCCESS);
}
