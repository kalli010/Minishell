/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 06:50:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 09:01:58 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	error(int status, int fd)
{
	if (status == 0)
	{
		perror("open error ");
		exit(EXIT_FAILURE);
	}
	if (status == 1)
	{
		perror("dup2 error");
		close(fd);
		exit(EXIT_FAILURE);
	}
}

int	check_if_uppercase(char *line)
{
	int	i;

	if (line[0] == '$' && line[1] != '\0')
	{
		i = 1;
		while (line[i])
		{
			if (!check_upper(line[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

char	*check_if_env(char **env, char *line)
{
	char	*path_env;

	if (check_if_uppercase(line))
	{
		path_env = ft_getenv(env, line + 1);
		if (path_env != NULL)
			return (path_env);
	}
	return (NULL);
}

int	here_doc(t_tree *root, t_helper *helper)
{
	int		fd;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		fd = open(".tmp_file", O_RDONLY, 0644);
		if (fd == -1)
			error(0, fd);
		if (dup2(fd, STDIN_FILENO) == -1)
			error(1, fd);
		find_command(root->first_child, helper);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}