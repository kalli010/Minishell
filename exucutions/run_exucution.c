/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exucution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/12 05:03:23 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void execute()
// {
//     t_tree  *tmp;
//     int c;
//     c = 0;

//     while(c == 0)
//     {
//         tmp = root;
//         while (tmp->first_child->content->type != COMMAND
// && tmp->first_child->i == 0)
//             tmp = tmp->first_child;
//         if(tmp->first_child->content->type == COMMAND)
//         {
//             if(tmp->content->typ == READERR )
//                 x = red(tmp->first_child,tmp->first_child->next_sibling);
//             tmp->i = 1;
//             if(tmp == root)
//                 c = 1;
//         }
//         if(tmp->first_child->i == 1)

//             if(tmp->content->type == PIPE)
//                 x = pipix(x, tmp->first_child->next_sibling);
//             tmp->i = 1;
//             if(tmp == root)
//                 c = 1;
//         }
//     }

void	execute(t_tree *root, t_helper *helper)
{
	(void)root;
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

void	find_command(t_tree *root, t_helper *helper)
{
	if (!root)
		return ;
	if (root->content->type == OUTPUT)
	{
		redirect_output(root, helper);
	}
	if (root->content->type == COMMAND || root->content->type == PATH_COMMAND)
	{
		execute(root, helper);
	}
	if (root->content->type == HEREDOC)
	{
		here_doc(root, helper);
	}
	find_command(root->first_child, helper);
	find_command(root->next_sibling, helper);
}
