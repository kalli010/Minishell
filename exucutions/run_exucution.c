/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exucution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/07 06:33:11 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void find_command(t_list *list, t_tree *root, t_helper *helper)
{
    (void)root;
    helper->cmd = get_path(helper, list);
    helper->option = get_opetions(helper, list);
	if (helper->cmd == NULL && helper->option == NULL)
	{
		
		printf("COMMAND NOT FOUND\n");
		free(helper->cmd);
		return ;
		
	}
    else if (helper->cmd != NULL)
	{
        execve(helper->cmd, helper->option, helper->envp);
    }
    free(helper->cmd);
    free_array(helper->option);
}
