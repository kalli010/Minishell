/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 05:28:11 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int finsh_status(pid_t pid)
{	
	int status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

void	exit_path(char *s, int status)
{
	if (status == ERROR_C)
	{
		if (s[0] == '/')
		{
			write(2, s, ft_strlen(s));
			write(2, ": No such file or directory\n", 28);
		}
		else
		{
			write(2, s, ft_strlen(s));
			write(2, ": command not found\n", 20);
		}
	}
	else if (status == P_DNIED)
	{
		write(2, s, ft_strlen(s));
		write(2, ": permission denied\n", 20);
	}
}

int	check_cmd(char *cmd, char *s, char **arg)
{
	if (access(cmd, F_OK) == -1)
	{	
		exit_path(s, ERROR_C);
		free(cmd);
		free_array(arg);
		return(ERROR_C);
	}
	else if (access(cmd, X_OK) == -1)
	{
		exit_path(s, P_DNIED);
		free(cmd);
		free_array(arg);
		return (P_DNIED);
	}
	free(cmd);
	free_array(arg);
	return (EXIT_FAILURE);
}

int execute(t_tree *root, t_helper *helper)
{
    pid_t pid;
    int status;

    status = 0;
    helper->cmd = get_path(helper, root->content);
    helper->option = get_options(helper, root->content); 
    pid = fork();
    if (pid == -1)
        return (perror("fork"),EXIT_FAILURE);
    if (pid == 0)
    {
        if (execve(helper->cmd, helper->option, helper->envp) == -1)
            status = check_cmd(helper->cmd, root->content->content, helper->option);
		return (status);
    }
    else
    {
        free(helper->cmd);
        free_array(helper->option);
        status = finsh_status(pid);
    } 
    return (status);
}

