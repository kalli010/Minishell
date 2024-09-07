/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_behavior.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 04:55:01 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/07 08:08:19 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	wait_for_finished(pid_t l_fork, pid_t r_fork)
{
	int	status;

	waitpid(l_fork, &status, 0);
	waitpid(r_fork, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		g_exit = WTERMSIG(status) + 128;
		return (WTERMSIG(status) + 128);
	}
	return (EXIT_FAILURE);
}

static int	right_pipe(int *fd, pid_t pid, t_tree *root, t_helper *helper)
{
	int	status;

	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		// signal(SIGINT,run_time);
		find_command(root, helper);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit = WEXITSTATUS(status);
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			g_exit = WTERMSIG(status) + 128;
			return (WTERMSIG(status) + 128);
		}
	}
	return (EXIT_FAILURE);
}

static int	left_pipe(int *fd, pid_t pid, t_tree *root, t_helper *helper)
{
	int	status;

	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
		// signal(SIGINT,run_time);
		find_command(root, helper);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit = WEXITSTATUS(status);
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			g_exit = WTERMSIG(status) + 128;
			return (WTERMSIG(status) + 128);
		}
	}
	return (EXIT_FAILURE);
}

int	execute_pipe(t_tree *root, t_helper *helper)
{
	int		fd[2];
	int		status;
	pid_t	r_fork;
	pid_t	l_fork;

	status = 0;
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
	}
	return (status);
}
