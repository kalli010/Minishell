/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:44:58 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/27 01:47:35 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_file *add_file(t_file **list, char *file_name, t_ttype type)
// {
//     t_file *new_file = malloc(sizeof(t_file));
//     t_file *current;

//     if (!new_file)
//         return (NULL);

//     new_file->file_name = strdup(file_name);
//     new_file->type = type;
//     new_file->next = NULL;
//     return (*list);
// }

// t_file *get_files(t_tree *root)
// {
//     t_file *file_list = NULL;
//     t_tree *current = root;

//     while (current && current->first_child && current->first_child->first_child)
//     {
//         if (current->content->type == OUTPUT || current->content->type == APPEND)
//         {
//             add_file(&file_list,current->content->content, current->content->type);
//         }
//         current = current->next_sibling;
//     }
//     return (file_list);
// }


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
int	open_fd(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		errors(0, fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
		errors(1, fd);
	return (fd);
}

int	redirect_input(t_tree *root, t_helper *helper)
{
	char	*file;
	int		fd;
	pid_t	pid;
	int		status;

	file = root->content->next->content;
	pid = fork();
	if (pid == 0)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd == -1)
			errors(0, fd);
		if (dup2(fd, STDIN_FILENO) == -1)
			errors(1, fd);
		close(fd);
		find_command(root->first_child, helper);
		exit(EXIT_SUCCESS);
	}
	else
		status = redirect_finished(pid);
	return (status);
}


int	redirect_output(t_tree *root, t_helper *helper)
{
	char	*file;
	int		fd;
	pid_t	pid;
	int		status;

	file = root->content->next->content;
	if (!ft_strncmp(root->content->content, ">>", 2))
		root->content->next->type = APPEND;
	pid = fork();
	if (pid == 0)
	{
		fd = open_fd(file, root->content->next->type== APPEND);
		find_command(root->first_child, helper);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
		status = redirect_finished(pid);
	return (status);
}
