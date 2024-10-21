/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:01:55 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/21 01:27:41 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	execute_parenthesis(t_tree *root, t_helper *helper, t_tree **rt)
{
	pid_t	pid;

	if (!root || !root->content)
		return (EXIT_FAILURE);
	if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
	{
		if (is_builtins(root))
			return (run_builtins(root, helper));
	}
	pid = fork();
	if (pid == 0)
	{
		if (find_command(root, helper, rt) != EXIT_SUCCESS)
		{
			cleanup(helper, rt);
			exit(EXIT_FAILURE);
		}
		cleanup(helper, rt);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
		return (handle_parent_process(pid));
	return (EXIT_FAILURE);
}
