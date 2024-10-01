/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/01 05:47:20 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

void	exit_path(char *s, int status)
{
	if (status == ERROR_C)
	{
		write(2, "minishell: ", 11);
		write(2, s, ft_strlen(s));
		write(2, ": command not found\n", 20);
	}
	else if (status == P_DNIED)
	{
		write(2, "minishell: ", 11);
		write(2, s, ft_strlen(s));
		write(2, ": Permission denied\n", 20);
	}
}

static int	finish_status(pid_t pid)
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
		if (WTERMSIG(status))
		{
			write(1, "\n", 1);
			return (WTERMSIG(status) + 128);
		}
	}
	return (EXIT_FAILURE);
}

int	prepare_command(t_tree *root, t_helper *helper)
{
	struct stat	buf;

	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);
	if (stat(helper->cmd, &buf) != 0)
	{
		exit_path(helper->cmd, ERROR_C);
		g_exit_status = ERROR_C;
		return (ERROR_C);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		write(2, helper->cmd, ft_strlen(helper->cmd));
		write(2, ": Is a directory\n", 17);
		g_exit_status = 126;
		return (126);
	}
	else if (access(helper->cmd, X_OK) != 0)
	{
		exit_path(helper->cmd, P_DNIED);
		g_exit_status = P_DNIED;
		return (P_DNIED);
	}
	return (EXIT_SUCCESS);
}

int	execute(t_tree *root, t_helper *helper)
{
	pid_t	pid;

	if (prepare_command(root, helper) != 0)
		return (ERROR_C);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		signal_handeler(CHILD);
		execve(helper->cmd, helper->option, helper->envp);
		g_exit_status = check_cmd(helper->cmd, root->content->content,
				helper->option);
		my_free(helper);
		exit(g_exit_status);
	}
	else
		g_exit_status = finish_status(pid);
	return (g_exit_status);
}
