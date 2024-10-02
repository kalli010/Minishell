/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/02 08:00:46 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



int check_root_content(t_tree  *root)
{
    if (!ft_strncmp(root->content->content,".", sizeof(".")))
    {
        printf("minishell : .: filename argument required\n");
        printf(".: usage: . filename [arguments]\n");
        return (2);
    }
    if (!ft_strncmp(root->content->content, "!", sizeof("!")))
    {
        printf(""); 
        return (1);
    }
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


// int flag = 0;
    
// static int execute_parenthesis(t_tree *root, t_helper *helper)
// {
//     pid_t pid;
//     int status;

//     if (!root || !root->content)
//         return (EXIT_FAILURE);
//     pid = fork();
//     if (pid == 0)
//     {
//         if (!!find_command(root, helper))
//             exit(EXIT_FAILURE);
//         exit(EXIT_SUCCESS);
//     }
//     else if (pid > 0)
//     {
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status)) 
//             return WEXITSTATUS(status); 
//         return (EXIT_FAILURE);
//     }
//     return (EXIT_FAILURE);

// }

int	find_command(t_tree *root, t_helper *helper)
{

    if (!root)
        return (EXIT_FAILURE);
    g_exit_status = check_root_content(root);
    if (g_exit_status !=  0)
        return (g_exit_status);
    // if (root->content->type == AND && flag == 0)
    // {
    //     flag = 1;
    //     return (execute_parenthesis(root, helper));
    // }

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
    {
        helper->redin = 0;
        helper->redout = 0;
        return (check_and_or(root, helper));
    }
    if (root->content->type == PIPE)
    {
        helper->redin = 0;
        helper->redout = 0;
        return (execute_pipe(root, helper));
    }
    if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
    {
        if (is_builtins(root) == true)
            return (run_builtins(root, helper));
        if (prepare_command(root, helper) != EXIT_SUCCESS)
            return g_exit_status;
        return (execute(root, helper));
    }
    return (EXIT_FAILURE);
}


