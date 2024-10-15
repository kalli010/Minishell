/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:54:10 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 16:48:03 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_existence(char *file, int flag)
{
	if (!file || access(file, F_OK) != 0)
	{
		g_helper.exit_status = 1;
		if (flag)
		{
			write(2, M_SHELL, 23);
			write(2, file, ft_strlen(file));
			write(2, ": No such file or directory\n", 29);
		}
		return (g_helper.exit_status);
	}
	return (g_helper.exit_status);
}

int	check_read(char *file)
{
	if (!file || access(file, R_OK) != 0)
	{
		g_helper.exit_status = 1;
		write(2, M_SHELL, 23);
		write(2, file, ft_strlen(file));
		write(2, " : Permission denied\n", 22);
		return (g_helper.exit_status);
	}
	return (g_helper.exit_status);
}

int	check_write_and_dir(char *file)
{
	struct stat	path_stat;

	if (stat(file, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		g_helper.exit_status = 1;
		write(2, M_SHELL, 23);
		write(2, file, ft_strlen(file));
		write(2, " : Is a directory\n", 19);
		return (g_helper.exit_status);
	}
	if (!file || access(file, W_OK) != 0)
	{
		g_helper.exit_status = 1;
		write(2, M_SHELL, 23);
		write(2, file, ft_strlen(file));
		write(2, " : Permission denied\n", 22);
		return (g_helper.exit_status);
	}
	return (g_helper.exit_status);
}

int	check_permission(char *file)
{
	if (!file || access(file, X_OK) != 0)
	{
		g_helper.exit_status = 1;
		write(2, M_SHELL, 23);
		write(2, file, ft_strlen(file));
		write(2, " : Permission denied\n", 22);
		return (g_helper.exit_status);
	}
	return (g_helper.exit_status);
}
