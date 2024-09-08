/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/08 13:20:54 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



static int execute_parenthesis(t_tree *root, t_helper *helper)
{
    if (!root || !root->content)
        return (EXIT_FAILURE);

    return (find_command(root, helper));
}

int	find_command(t_tree *root, t_helper *helper)
{
    if (!root)
        return (EXIT_FAILURE);
    if (root->content->type == PARENTHESIS)
        return (execute_parenthesis(root->first_child, helper));
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


