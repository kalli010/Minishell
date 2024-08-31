/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/31 09:03:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_path(char *s, int status)
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

void	check_cmd(char *cmd, char *s, char **arg)
{
	if (access(cmd, F_OK) == -1)
		exit_path(s, ERROR_C);
	else if (access(cmd, X_OK) == -1)
		exit_path(s, P_DNIED);
	free(cmd);
	free_array(arg);
	exit(EXIT_FAILURE);
}

int	execute(t_tree *root, t_helper *helper)
{
	pid_t	pid;
	int		status;

	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), (EXIT_FAILURE));
	if (pid == 0)
	{
		if (execve(helper->cmd, helper->option, helper->envp) == -1)
			check_cmd(helper->cmd, root->content->content, helper->option);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(helper->cmd);
		free_array(helper->option);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
