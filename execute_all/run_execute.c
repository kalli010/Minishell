/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/17 23:52:12 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_only_slashes(t_tree *root)
{
    char *str;
    int i;

    str =  root->content->content;
    i = 0;
    while (str[i])
    {
        if (str[i] != '/')
            return (0);
        i++;
    }
    return (1);
}

int check_root_content(t_tree  *root)
{
    if (!ft_strncmp(root->content->content,".",sizeof(".")))
    {
        printf("minishell :.: filename argument required\n");
        printf(".: usage: . filename [arguments]\n");
        return (2);
    }
    if (!ft_strncmp(root->content->content,"!",sizeof("!")))
    {
        printf("");
        return (1);
    }
    if (!ft_strncmp(root->content->content,"..",sizeof("..")))
    {
        printf("..: command not found\n");
        return (127);
    }
    if (!ft_strncmp(root->content->content, "//", 1) && is_only_slashes(root))
    {
        printf("minishell: %s: Is a directory\n", root->content->content);
        return (126);
    }
    return (0);
}

int flag = 0;
    
static int execute_parenthesis(t_tree *root, t_helper *helper)
{
    pid_t pid;
    int status;

    if (!root || !root->content)
        return (EXIT_FAILURE);
    // printf("helooooo\n");
    pid = fork();
    if (pid == 0)
    {
        if (!!find_command(root, helper))
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) 
            return WEXITSTATUS(status); 
        return (EXIT_FAILURE);
    }
    return (EXIT_FAILURE);

}

int	find_command(t_tree *root, t_helper *helper)
{

    if (!root)
        return (EXIT_FAILURE);
    g_exit_status = check_root_content(root);
    if (g_exit_status !=  0)
        return (g_exit_status);
    if (root->content->type == AND && flag == 0)
    {
        flag = 1;
        return (execute_parenthesis(root, helper));
    }
    if (root->content->type == INPUT)
    {
        if (redirect_input(root, helper) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
	if (root->content->type == APPEND ||  root->content->type == OUTPUT)
    {
        if (redirect_output(root, helper) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    if (root->content->type == AND || root->content->type == OR)
        return (check_and_or(root, helper));
    if (root->content->type == PIPE)
        return (execute_pipe(root, helper));
    if ((root->content->type == COMMAND || root->content->type == PATH_COMMAND)
        && (root->first_child == NULL || root->first_child->content == NULL
            || root->first_child->content->type == OPTIONS))
    {
        if (is_builtins(root) == true)
            return (run_builtins(root, helper));
        else
            return (execute(root, helper));
    }
    return (EXIT_FAILURE);
}


