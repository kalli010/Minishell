/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:44:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/25 19:10:36 by ayel-mou         ###   ########.fr       */
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
	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_WRONLY, 0644);
		if (fd == -1)
			errors(0, fd);
		if (dup2(fd, STDIN_FILENO) == -1)
			errors(1, fd);
		execute(root->first_child, helper);
		close(fd);
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
	printf(" check redirect -->   %s \n",root->first_child->content->content);
	if (root->first_child->content->type != COMMAND)
		find_command(root->first_child,helper);
	
	else
	{
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
				execute(root->first_child, helper);
				close(fd);
				exit(EXIT_SUCCESS);
			}
			else
				waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status))
        return (WEXITSTATUS(status));
	return (1);
}
