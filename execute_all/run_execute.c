/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/25 20:48:56 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int	execute_right_pipe(t_tree *root, t_helper *helper)
{
	int	status;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
int	execute_left_pipe(t_tree *root, t_helper *helper)
{
	int	status;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	execute_pipe(t_tree *root, t_helper *helper)
{
	int		fd[2];
	pid_t	r_fork;
	pid_t	l_fork;
	int		status;

	// printf("first child is == %s\n", root->first_child->content->content);
	// printf("next sibling is == %s\n",root->first_child->next_sibling->content->content);
	if (pipe(fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	r_fork = fork();
	if (r_fork < 0)
		return (perror("fork "), EXIT_FAILURE);
	if (root->first_child)
	{
		if (root->first_child->next_sibling)
		{
			
		}
		l_fork =  fork();
		if (l_fork = 0)
			execute_left_pipe(root->first_child->next_sibling,helper);
		else
			waitpid(l_fork,&status,0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (EXIT_FAILURE);
	}
}
int	find_command(t_tree *root, t_helper *helper)
{
	if (!root)
		return (EXIT_FAILURE);
	if ((root->content->type == COMMAND || root->content->type == PATH_COMMAND)
		&& (root->first_child == NULL || root->first_child->content == NULL
			|| root->first_child->content->type == OPTIONS))
	{
		if (root->next_sibling != NULL)
			return (EXIT_FAILURE);
		return (execute(root, helper));
		return (EXIT_FAILURE);
	}
	if (root->content->type == OUTPUT || root->content->type == APPEND)
		return (redirect_output(root, helper));
	if (root->content->type == INPUT)
		return (redirect_input(root, helper));
	if (root->content->type == HEREDOC)
		return (here_doc(root, helper));
	if (root->content->type == PIPE)
		return (execute_pipe(root, helper));
	return (1);
}
