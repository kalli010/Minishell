/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/04 22:53:07 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int handle_redirections(t_tree *root, t_helper *helper);
int check_root_content(t_tree  *root)
{
    if (!ft_strncmp(root->content->content,".", sizeof(".")))
    {
        printf("minishell : .: filename argument required\n");
        printf(".: usage: . filename [arguments]\n");
        return (2);
    }
    if (!ft_strncmp(root->content->content, "!", sizeof("!")))
        return (1);
    if (!ft_strncmp(root->content->content, "..", sizeof("..")))
    {
        printf("..: command not found\n");
        return (127);
    }
    if (!ft_strncmp(root->content->content, "//", 1) && is_only_slashes(root))
    {
        printf("minishell: %s: Is a directory\n", root->content->content);
        return (126);
    }
    if (is_only_bs(root))
        return (127);  
    return (0);
}


static int execute_parenthesis(t_tree *root, t_helper *helper)
{
    pid_t pid;
    int status;

    if (!root || !root->content)
        return (EXIT_FAILURE);
    if (handle_redirections(root->first_child, helper) != EXIT_SUCCESS)
        return (EXIT_FAILURE);

    pid = fork();
    if (pid == 0)
    {
        if (find_command(root->first_child, helper) != EXIT_SUCCESS)
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


int handle_redirections(t_tree *root, t_helper *helper)
{
    if (root->content->type == INPUT)
    {
        if (redirect_input(root, helper) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    if (root->content->type == APPEND || root->content->type == OUTPUT)
    {
        if (redirect_output(root, helper) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int handle_logical(t_tree *root, t_helper *helper)
{
    helper->redin = 0;
    helper->redout = 0;
    if (root->content->type == AND || root->content->type == OR)
        return (check_and_or(root, helper));
    if (root->content->type == PIPE)
        return (execute_pipe(root, helper));
    return (EXIT_SUCCESS);
}

int find_command(t_tree *root, t_helper *helper)
{
    if (!root)
        return (EXIT_FAILURE);
    
    g_exit_status = check_root_content(root);
    if (g_exit_status != 0)
        return (g_exit_status);
    if (root->content->type == AND && root->content->in == 1)
    {
        root->content->in = 0;
        return (execute_parenthesis(root, helper));
    }
    if (handle_redirections(root, helper) == EXIT_FAILURE && root->content->in != 1)
        return (EXIT_FAILURE);
    if (handle_logical(root, helper) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
    {
        if (is_builtins(root) == true)
            return (run_builtins(root, helper));
        return (execute(root, helper));
    }
    return (EXIT_FAILURE);
}


