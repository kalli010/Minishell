/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:33:17 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/13 20:02:25 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
int check_and_or(t_tree *root, t_helper *helper,t_tree **rt)
{
    int status;
    // if (root && root->first_child && root->first_child->next_sibling)
    // {
        if (root->content->type == AND)
        {  
            status = find_command(root->first_child, helper,rt);
            if (status == 0)
                return (find_command(root->first_child->next_sibling, helper, rt));
            else
                return (status); 
        }
        else if (root->content->type == OR)
        {
            status = find_command(root->first_child, helper, rt);
            if (status == 130)
                return (status);
            if (status != 0)
                return (find_command(root->first_child->next_sibling, helper, rt));
            else
                return (status); 
        }
    // }      
    return (EXIT_SUCCESS);
}
