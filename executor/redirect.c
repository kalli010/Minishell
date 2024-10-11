/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:44:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/11 18:25:13 by ayel-mou         ###   ########.fr       */
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

int	open_fd(char *file, int type)
{
	int	fd;
	int	duped_fd;

	fd = open_files(file, type);
	if (fd == -1)
		return (-1);
	if (type == INPUT)
		duped_fd = STDIN_FILENO;
	else
		duped_fd = STDOUT_FILENO;
	return (duplicate_fd(fd, duped_fd, file));
}

int	redirect_all(t_tree *root, t_helper *helper,t_tree **rt)
{
	pid_t		pid;
	t_redirect	*redlst;

	if (!ft_strncmp(root->content->content, ">>", 2))
		root->content->next->type = APPEND;
	pid = fork();
	if (pid == 0)
	{
		redlst = init_redirect_lst(&root);
		if (!redlst)
			exit(EXIT_FAILURE);
		g_exit_status = exec_redirections(redlst, helper);
		if (g_exit_status != 0)
		{
			clean_env((*helper->envp));
			clean_env((*helper->xenv));
			free_tree(*rt);
			free(helper->redfile);
			my_free(helper);
			free_redirect_list(&redlst);
			exit(g_exit_status);
		}
		free_redirect_list(&redlst);
		find_command(root, helper, NULL);
		clean_env((*helper->envp));
		clean_env((*helper->xenv));
		free_tree(*rt);
		free(helper->redfile);
		my_free(helper);
		exit(EXIT_SUCCESS);
	}
	else
		return (redirect_finished(pid));
}
