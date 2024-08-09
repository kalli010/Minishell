/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exucution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:21:08 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/09 07:03:05 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void find_command(t_list *list, t_tree *root, t_helper *helper)
{
    (void)root;
    if (list->type == HEREDOC)
        here_doc(list,helper);
    list = list->next;
    list = list->next;
    if (list->type == COMMAND)
    {
        helper->cmd = get_path(helper, list);
        helper->option = get_options(helper, list);
         if (helper->cmd == NULL && helper->option == NULL)
         {
                printf("%s: command not found\n", list->content);
                free(helper->cmd);
         }
        else if (helper->cmd != NULL)
            execve(helper->cmd, helper->option, helper->envp);
        free(helper->cmd);
        free_array(helper->option);

    }
    if (ft_strncmp(list->content,"env\n",ft_strlen(list->content)) == 0)
        ft_env(helper->envp);
    if (ft_strncmp(list->content,"pwd\n",ft_strlen(list->content)) == 0)
        ft_pwd();
}
