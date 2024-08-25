/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exucution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/24 03:34:18 by ayel-mou         ###   ########.fr       */
=======
/*   Updated: 2024/08/24 22:29:46 by ayel-mou         ###   ########.fr       */
>>>>>>> fcfee4cc5cb5357f3b8fa325250676f2d5115b4d
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



void	execute(t_tree *root, t_helper *helper)
{
	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);
	if (!helper->cmd && !helper->option)
	{
		free(helper->cmd);
		return ;
	}
	execute_command(helper->cmd, helper->option, helper->envp);
	free(helper->cmd);
	free_array(helper->option);
}



void execute_pipe(t_tree *root, t_helper *helper)
{
    int fd[2];
    pid_t r_fork;
	// pid_t l_fork;
	// printf("first child is == %s\n", root->first_child->content->content);
	// printf("next sibling is == %s\n", root->first_child->next_sibling->content->content);
    if (pipe(fd) == -1)
<<<<<<< HEAD
        return;
    pid = fork();
    if (pid == -1)
=======
>>>>>>> fcfee4cc5cb5357f3b8fa325250676f2d5115b4d
        return ;

    r_fork = fork();
    if (r_fork == -1)
        return ;
	// if (r_fork == 0)
	// {
		
	// }
    if (r_fork == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
		if (root->first_child->content->type == PIPE)
			execute_pipe(root->first_child,helper);
        execute(root->first_child, helper);
		exit(EXIT_SUCCESS);
    }
    else
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
		waitpid(r_fork, NULL, 0);
		execute(root->first_child->next_sibling, helper);
		//exit(EXIT_SUCCESS);
    }
	// execute_pipe(root->first_child,helper);
}

void	find_command(t_tree *root, t_helper *helper)
{
	if (!root)
		return ;
	  if ((root->content->type == COMMAND || root->content->type == PATH_COMMAND) &&
        (root->first_child == NULL || root->first_child->content == NULL || 
        root->first_child->content->type == OPTIONS))
    {
		if (root->next_sibling != NULL)
			return ;
        execute(root, helper);
        return;
    }
	if (root->content->type == OUTPUT || root->content->type == APPEND)
	{
		redirect_output(root, helper);
	}
	if (root->content->type == INPUT)
	{
		redirect_input(root, helper);
	}
	if (root->content->type == HEREDOC)
	{
		here_doc(root, helper);
	}
	if (root->content->type == PIPE)
	{
		execute_pipe(root,helper);
	}
	// find_command(root->first_child, helper);
	// find_command(root->next_sibling, helper);
}
