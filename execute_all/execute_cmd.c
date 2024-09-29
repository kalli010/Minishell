/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:26:42 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/29 06:35:03 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void exit_path(char *s, int status)
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
        g_exit_status = WTERMSIG(status) + 128;
        if (WTERMSIG(status))
        {
            write(1, "\n", 1);
            return (WTERMSIG(status) + 128);
        }
    }
    return (EXIT_FAILURE);
}

int prepare_command(t_tree *root, t_helper *helper)
{
    helper->cmd = get_path(helper, root->content);
    helper->option = get_options(helper, root->content);

    if (!helper->cmd)
    {
        exit_path(root->content->content, ERROR_C);
        g_exit_status = ERROR_C;
        my_free(helper);
        return (ERROR_C);
    }
    return (EXIT_SUCCESS);
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
        execve(helper->cmd, helper->option, helper->envp);
        status = check_cmd(helper->cmd, root->content->content, helper->option);
        g_exit_status = status;
        my_free(helper);
        exit(status);
    }
    else 
    {
        status = finish_status(pid);
        g_exit_status = status;
    }
    return status;
}
















