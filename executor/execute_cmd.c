/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 18:30:41 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	finish_status(pid_t pid)
{
	int	status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_helper.exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
			g_helper.exit_status = WTERMSIG(status) + 128;
		return (g_helper.exit_status);
	}
	return (EXIT_FAILURE);
}

int prepare_command(t_tree *root, t_helper *helper)
{
    char *path;

    path = ft_getenv(helper->envp, "PATH");
    if (!path || !*path)
    {
        helper->cmd = get_path_of_cpath(root->content);
        if (!helper->cmd)
            return no_file_no_dir(root->content->content);
    }
    else
        helper->cmd = get_path(helper, root->content); 
    helper->option = get_options(helper, root->content);
	free(path);
    if (!helper->cmd)
	{	if (g_helper.flag == 1)
			return no_file_no_dir(root->content->content);
        return command_not_found(root->content->content);
	}
    return (EXIT_SUCCESS);
}

static int child_process(t_helper *helper, t_tree *root)
{
	struct stat path_stat;

	if (prepare_command(root, helper) != 0)
		return (ERROR_C);
	if (stat(helper->cmd, &path_stat) != 0)
		return no_file_no_dir(helper->cmd);
	if (S_ISDIR(path_stat.st_mode))
		return is_dir(helper->cmd);
	if (get_permission(helper->cmd))
		return 126; 
	execve(helper->cmd, helper->option, helper->envp);
	return (EXIT_SUCCESS);
}
 

int	execute(t_tree *root, t_helper *helper,t_tree **rt)
{
	pid_t	pid;
	(void)rt;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	
	if (pid == 0)
	{
		signal_handeler(CHILD);
		g_helper.exit_status = child_process(helper, root);
		cleanup(helper,rt);
		exit(g_helper.exit_status);
	}
	else
		g_helper.exit_status = finish_status(pid);
	return (g_helper.exit_status);
}
