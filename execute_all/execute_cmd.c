/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/03 03:49:22 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_exec_access(char *filename)
{
	if (filename[0] == '.' || filename[0] == '/')
	{
    	if (access(filename, X_OK) != 0)
    	{
        	perror("minishell: Permission denied");
        	return 126;
    	}
	}
    return 0;
}

int command_not_found(char *cmd)
{
	write(2,"minishell: ",12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	g_exit_status = 127;
	return (g_exit_status);
}
int	is_dirc(char *dir)
{
	g_exit_status = 126;
	write(2,"minishell: ",12);
		write(2, dir, ft_strlen(dir));
		write(2, " : Is a directory\n", 19);
		return (g_exit_status);
}


static int finish_status(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		
		if (WTERMSIG(status))
			g_exit_status = WTERMSIG(status) + 128;
		return (g_exit_status);
	}
	return (EXIT_FAILURE);
}

int prepare_command(t_tree *root, t_helper *helper)
{
	helper->cmd = get_path(helper, root->content);
	helper->option = get_options(helper, root->content);
	if (!helper->cmd)
	{
		printf("%s \n",helper->cmd);
		dprintf(2,"ana hana\n");
		g_exit_status = ERROR_C;
		return (ERROR_C);
	}
	return (EXIT_SUCCESS);
}
static int child_process(t_helper *helper, t_tree *root)
{
	(void)root;
	struct stat path_stat;
    if (check_existence(helper->cmd, 0) == 127)
        return command_not_found(helper->cmd);
    if (stat(helper->cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
        return is_dirc(helper->cmd);
    if (get_exec_access(helper->cmd))
        return (g_exit_status = 126);
    execve(helper->cmd, helper->option, helper->envp);
    return EXIT_FAILURE;
}


int execute(t_tree *root, t_helper *helper)
{
    int status;
    pid_t pid;

    if (prepare_command(root, helper) != 0)
        return (ERROR_C);
    pid = fork();
    if (pid == -1)
        return (perror("fork"), EXIT_FAILURE);
    if (pid == 0) 
	{
        signal_handeler(CHILD);
        status = child_process(helper, root);
        exit(status);
    }
    else 
    {
        status = finish_status(pid);
        g_exit_status = status;
    }
    return status;
}




