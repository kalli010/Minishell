/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_behavior.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 04:55:01 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 18:15:15 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	wait_for_finished(pid_t l_fork, pid_t r_fork)
{
	int	status;

	if (waitpid(l_fork, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_helper.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_helper.exit_status = WTERMSIG(status) + 128;
	}
	if (waitpid(r_fork, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_helper.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_helper.exit_status = WTERMSIG(status) + 128;
	}
	return (g_helper.exit_status);
}

static void	right_pipe(int *fd, t_tree *root, t_helper *helper, t_tree **rt)
{
	dup2(fd[0], STDIN_FILENO);
	(close(fd[0]), close(fd[1]));
	if (find_command(root, helper, rt))
	{
		cleanup(helper, rt);
		exit(g_helper.exit_status);
	}
	cleanup(helper, rt);
	exit(EXIT_SUCCESS);
}

static void	left_pipe(int *fd, t_tree *root, t_helper *helper, t_tree **rt)
{
	dup2(fd[1], STDOUT_FILENO);
	(close(fd[0]), close(fd[1]));
	if (find_command(root, helper, rt))
	{
		cleanup(helper, rt);
		exit(g_helper.exit_status);
	}
	cleanup(helper, rt);
	exit(EXIT_SUCCESS);
}

int	execute_pipe(t_tree *root, t_helper *helper, t_tree **rt)
{
	int		fd[2];
	int		status;
	pid_t	r_fork;
	pid_t	l_fork;

	status = 0;
  if (pipe(fd) == -1)
    return (perror("pipe"), EXIT_FAILURE);
  l_fork = fork();
  if (l_fork < 0)
    return (perror("fork"), EXIT_FAILURE);
  if (l_fork == 0)
    left_pipe(fd, root->first_child, helper, rt);
  r_fork = fork();
  if (r_fork < 0)
    return (perror("fork"), EXIT_FAILURE);
  if (r_fork == 0)
  {
    if(root->first_child != NULL)
      right_pipe(fd, root->first_child->next_sibling, helper, rt);
  }
  close(fd[0]);
  close(fd[1]);
  status = wait_for_finished(l_fork, r_fork);
	return (status);
}
