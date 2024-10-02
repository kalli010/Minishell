/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:42:50 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/02 09:15:10 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_only_bs(t_tree *root)
{
	char	*str;
	int		i;

	str = root->content->content;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			return (EXIT_SUCCESS);
		i++;
	}
	write(2, "minishell :", 12);
	write(2, str, ft_strlen(str));
	write(2, " : command not found\n", 22);
	return (EXIT_FAILURE);
}

int	is_only_slashes(t_tree *root)
{
	char	*str;
	int		i;

	str = root->content->content;
	i = 0;
	while (str[i])
	{
		if (str[i] != '/')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	helper_check_cmd(char *cmd, char *s)
{
	struct stat	dir;

	if (access(cmd, F_OK  | X_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied\n", 20);
		g_exit_status = 126;
		return (g_exit_status);
	}
	if (stat(cmd, &dir) != 0)
	{
		exit_path(s, ERROR_C);
		return (ERROR_C);
	}
	if (S_ISDIR(dir.st_mode))
	{
		write(2, cmd, strlen(cmd));
		write(2, ": Is a directory\n", 17);
		return (P_DNIED);
	}
	return (EXIT_FAILURE);
}

int	check_cmd(char *cmd, char *s, char **arg)
{
	int	status;

	status = helper_check_cmd(cmd, s);
	if (status != EXIT_FAILURE)
	{
		free(cmd);
		free_array(arg);
		return (status);
	}
	if (access(cmd, X_OK) != 0)
	{
		exit_path(s, P_DNIED);
		free(cmd);
		free_array(arg);
		return (P_DNIED);
	}
	if (access(cmd, F_OK) != 0)
	{
		exit_path(s, ERROR_C);
		free(cmd);
		free_array(arg);
		return (ERROR_C);
	}
	return (EXIT_FAILURE);
}

int	errors(char *file, int status, int fd)
{
	g_exit_status = 1;
	if (status == 0)
	{
        write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, " No such file or directory\n", 28);
		return (g_exit_status);
	}
	if (status == 1)
	{
		perror("dup2 error");
		close(fd);
		return (g_exit_status);
	}
	if (status == 2)
	{
		write(2, "minishell: ", 11);
		write(2, file, ft_strlen(file));
		write(2, " ambiguous redirect\n", 21);
		return (g_exit_status);
	}
	return (EXIT_SUCCESS);
}
