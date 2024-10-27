/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:44:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/21 01:34:47 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirect_finished(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_helper.exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		g_helper.exit_status = WTERMSIG(status) + 128;
		return (WTERMSIG(status) + 128);
	}
	return (EXIT_FAILURE);
}

int	open_files(char *file, int type)
{
	int	fd;

	if (!file || !*file)
		return (errors("Invalid file\n", 0, -1), -1);
	if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == OUTPUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == INPUT)
		fd = open(file, O_RDONLY, 0644);
	else
		return (errors("Invalid file type\n", 0, -1), -1);
	if (fd == -1)
		return (errors("Invalid file\n", 0, -1), -1);
	return (fd);
}

int	duplicate_fd(int fd, int duped_fd, char *file)
{
	if (dup2(fd, duped_fd) == -1)
	{
		errors(file, 1, fd);
		close(fd);
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	execute_child_process(t_tree *root, t_helper *helper, t_tree **rt)
{
	t_redirect	*redlst;

	redlst = init_redirect_lst(&root);
	if (!redlst)
	{
		cleanup(helper, rt);
		free_redirect_list(&redlst);
		exit(EXIT_FAILURE);
	}
	g_helper.exit_status = exec_redirections(redlst, helper);
	if (g_helper.exit_status != 0)
	{
		free_redirect_list(&redlst);
		cleanup(helper, rt);
		exit(g_helper.exit_status);
	}
	free_redirect_list(&redlst);
	if (find_command(root, helper, rt))
	{
		cleanup(helper, rt);
		exit(EXIT_FAILURE);
	}
	cleanup(helper, rt);
	exit(EXIT_SUCCESS);
}

int	redirect_all(t_tree *root, t_helper *helper, t_tree **rt)
{
	pid_t	pid;

	if (!ft_strncmp(root->content->content, ">>", 2))
		root->content->next->type = APPEND;
	pid = fork();
	if (pid == 0)
		execute_child_process(root, helper, rt);
	else
		return (redirect_finished(pid));
	return (0);
}
