/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exucution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/10 03:47:26 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void find_command(t_list *list, t_tree *root, t_helper *helper)
{
    if (root == NULL)
        return ;
    if (list->type == HEREDOC)
        here_doc(list,helper);
   // list = list->next;
   // list = list->next;
    char *a[2];

    a[0] = list->content;
    a[1] = NULL;
   if (list->type == PATH_COMMAND)
   {
     if (execve(list->content,a, helper->envp) == 1)
        printf("ZAKI ZAMAL \n");

    
    }
    // list = list->next;
    // list = list->next;
    if (list->type == COMMAND)
    {
        helper->cmd = get_path(helper, list);
        helper->option = get_options(helper, list);
         if (helper->cmd == NULL && helper->option == NULL)
         {
                printf("%s: command not found\n", list->content);
                free(helper->cmd);
         }
        execute_command(helper->cmd,helper->option,helper->envp);
        // else if (helper->cmd != NULL)
        //     execve(helper->cmd, helper->option, helper->envp);
        free(helper->cmd);
        free_array(helper->option);

    }
    else if (ft_strncmp(list->content,"env\n",ft_strlen(list->content)) == 0)
        ft_env(helper->envp);
    else if (ft_strncmp(list->content,"pwd\n",ft_strlen(list->content)) == 0)
        ft_pwd();
}
