/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/07 14:47:07 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell.h>

static int finish_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_helper->exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		g_helper->flag = true;
		g_helper->exit_status = WTERMSIG(status) + 128;
		if (WTERMSIG(status))
		{	write(1,"\n",1);
			return (WTERMSIG(status) + 128);
		}
	}
	return (EXIT_FAILURE);
}

void exit_path(char *s, int status)
{
	if (status == ERROR_C)
	{
		if (s[0] == '/')
		{
			write(2, s, ft_strlen(s));
			write(2, ": No such file or directory\n", 28);
		}
		else
		{
			write(2, s, ft_strlen(s));
			write(2, ": command not found\n", 20);
		}
	}
	else if (status == P_DNIED)
	{
		write(2, s, ft_strlen(s));
		write(2, ": permission denied\n", 20);
	}
}

int check_cmd(char *cmd, char *s, char **arg)
{
	if (access(cmd, F_OK) == -1)
	{
		exit_path(s, ERROR_C);
		free(cmd);
		free_array(arg);
		return (ERROR_C);
	}
	else if (access(cmd, X_OK) == -1)
	{
		exit_path(s, P_DNIED);
		free(cmd);
		free_array(arg);
		return (P_DNIED);
	}
	free(cmd);
	free_array(arg);
	return (EXIT_FAILURE);
}

int execute(t_tree *root, t_helper *helper)
{
	int		status;

	status = 0;
	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);
	helper->pid = fork();
	if (helper->pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (helper->pid == 0)
	{
		signal_handeler(CHILD);
		if (execve(helper->cmd, helper->option, helper->envp) == -1)
			status = check_cmd(helper->cmd, root->content->content,
					helper->option);
		exit(status);
	}
	else
	{
		free(helper->cmd);
		free_array(helper->option);
		status = finish_status(helper->pid);
	}
	return status;
}

