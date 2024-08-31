/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/30 10:54:47 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	wait_for_finished(pid_t l_fork, pid_t r_fork)
{
	int	status;

	waitpid(l_fork, &status, 0);
	waitpid(r_fork, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	right_pipe(int *fd, pid_t pid, t_tree *root, t_helper *helper)
{
	int	status;

	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		find_command(root, helper);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	left_pipe(int *fd, pid_t pid, t_tree *root, t_helper *helper)
{
	int	status;

	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		find_command(root, helper);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	execute_pipe(t_tree *root, t_helper *helper)
{
	int		fd[2];
	int		status;
	pid_t	r_fork;
	pid_t	l_fork;

	if (pipe(fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	if (root->first_child && root->first_child->next_sibling)
	{
		l_fork = fork();
		if (l_fork < 0)
			return (perror("fork"), EXIT_FAILURE);
		if (l_fork == 0)
			left_pipe(fd, l_fork, root->first_child, helper);
		r_fork = fork();
		if (r_fork < 0)
			return (perror("fork"), EXIT_FAILURE);
		if (r_fork == 0)
			right_pipe(fd, r_fork, root->first_child->next_sibling, helper);
		close(fd[0]);
		close(fd[1]);
		status = wait_for_finished(l_fork, r_fork);
		return (status);
	}
	return (EXIT_FAILURE);
}

int	find_command(t_tree *root, t_helper *helper)
{
	
	if (!root)
		return (EXIT_FAILURE);
	if ((root->content->type == COMMAND || root->content->type == PATH_COMMAND)
		&& (root->first_child == NULL || root->first_child->content == NULL
			|| root->first_child->content->type == OPTIONS))
	{
		if (is_builtins(root->content) == true)
			return (run_builtins(root->content, helper));
		else
			return (execute(root, helper));
	}
	if (root->content->type == OUTPUT || root->content->type == APPEND)
		return (redirect_output(root, helper));
	if (root->content->type == INPUT)
	{
		return (redirect_input(root, helper));
	}
	if (root->content->type == HEREDOC)
		return (here_doc(root, helper));
	if (root->content->type == AND || root->content->type == OR)
		return (check_and_or(root, helper));
	if (root->content->type == PIPE)
		return (execute_pipe(root, helper));
	return (EXIT_FAILURE);
	
}
