/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:42:50 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/05 00:03:24 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_slash(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == '/')
			return (1);
	return (0);
}

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
