/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:44:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/03 02:43:41 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirect_finished(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		g_exit_status = WTERMSIG(status) + 128;
		return (WTERMSIG(status) + 128);
	}
	return (EXIT_FAILURE);
}

int	open_fd(t_helper *helper,char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		errors(file, 0, fd);
	if (!helper->redout)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			errors(file, 1, fd);
		helper->redout = 1;
	}
	return (fd);
}

int	redirect_input_handler(char *file, t_tree *root, t_helper *helper)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
	{
		errors(file, 0, fd);
		return (g_exit_status);
	}
	if (!helper->redin)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			errors(file, 1, fd);
			close(fd);
			return (g_exit_status);
		}
		helper->redin  = 1;
	}
	close(fd);
	find_command(root->first_child, helper);
	return (EXIT_SUCCESS);
}

int	redirect_input(t_tree *root, t_helper *helper)
{
	char	*file;
	pid_t	pid;
	int		status;

	if (root->content->i == 2)
		return (errors(root->content->next->content, 2, 0), g_exit_status);
	file = root->content->next->content;
	if (check_existence(file, 1) || check_read(file))
		return (g_exit_status);
	pid = fork();
	if (pid == 0)
	{
		if (redirect_input_handler(file, root, helper) != EXIT_SUCCESS)
			exit(g_exit_status);
		exit(EXIT_SUCCESS);
	}
	else
	{
		status = redirect_finished(pid);
		g_exit_status = status;
	}
	return (g_exit_status);
}

int	redirect_output(t_tree *root, t_helper *helper)
{
	char	*file;
	int		fd;
	pid_t	pid;

	if (root->content->i == 2)
		return (errors(root->content->next->content, 2, 0), g_exit_status);
	file = root->content->next->content;
	if (!check_existence(file, 0) && check_write_and_dir(file))
		return (g_exit_status);
	if (!ft_strncmp(root->content->content, ">>", 2))
		root->content->next->type = APPEND;
	pid = fork();
	if (pid == 0)
	{
		fd = open_fd(helper,file, root->content->next->type == APPEND);
		find_command(root->first_child, helper);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
		g_exit_status = redirect_finished(pid);
	return (g_exit_status);
}
