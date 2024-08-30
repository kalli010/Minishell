/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:44:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/26 22:06:44 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	errors(int status, int fd)
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

int	redirect_input(t_tree *root, t_helper *helper)
{
	char	*file;
	int		fd;
	pid_t	pid;
	int		status;

	status = 0;
	file = root->first_child->content->content;
	dprintf(2, "file : %s\n", file);
	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd == -1)
			errors(0, fd);
		if (dup2(fd, STDIN_FILENO) == -1)
			errors(1, fd);
		close(fd);
		// dprintf(2, "salam\n");
		// dprintf(2, " root is %s ---> \n",root->first_child->content->content);
		find_command(root->next_sibling,helper);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
        return (WEXITSTATUS(status));
	return (1);
}

int	redirect_output(t_tree *root, t_helper *helper)
{
	char	*file;
	int		fd;
	pid_t	pid;
	int status;
	
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		file = root->first_child->next_sibling->content->content;
		if (root->content->type == APPEND)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			errors(0, fd);
		if (dup2(fd, STDOUT_FILENO) == -1)
			errors(1, fd);
		find_command(root->first_child,helper);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
        return (WEXITSTATUS(status));
	return (1);
}

