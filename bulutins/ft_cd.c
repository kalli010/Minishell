/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/29 05:37:18 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static int cd_errors(void)
{
    g_exit_status = 1;
    write(2, "minishell : cd : too many arguments\n", 37);
    return (g_exit_status);
}

static void update_pwd(char *old, char *curr, t_helper *helper)
{
    char *old_pwd;
    char *curr_pwd;
    t_list oldpwd_node;
    t_list currpwd_node;

    old_pwd = ft_strjoin("OLDPWD=", old);
    curr_pwd = ft_strjoin("PWD=", curr);
    oldpwd_node.content = old_pwd;
    oldpwd_node.next = NULL;
    currpwd_node.content = curr_pwd;
    currpwd_node.next = NULL;
    set_var(&oldpwd_node, &(helper->envp));
    set_var(&currpwd_node, &(helper->envp));
    free(old_pwd);
    free(curr_pwd);
}


int change_directory(char *go_path)
{
    g_exit_status = 0;
    if (!is_directory(go_path))
    {
        handle_cd_error(go_path, 1);
        free(go_path);
        g_exit_status = 1;
        return (g_exit_status);
    }
    if (chdir(go_path) != 0)
    {
        handle_cd_error(go_path, 2);
        free(go_path);
        g_exit_status = 1;
        return (g_exit_status);
    }
    free(go_path);
    return (g_exit_status);
}


int ft_cd(t_list *list, t_helper *helper)
{
    char *old_pwd;
    char *curr_pwd;
    
    if (!list)
    {
        g_exit_status = 1;
        return (g_exit_status);
    }
    if (count_arg(list) != 1 && count_arg(list) != 0)
        return cd_errors();
    old_pwd = getcwd(NULL, 0);
    char *go_path = get_target_path(list, helper);
    if (!go_path)
    {
        g_exit_status = 1;
        return (g_exit_status);
    }
    if (change_directory(go_path) == 0) 
    {
        curr_pwd = getcwd(NULL, 0); 
        update_pwd(old_pwd, curr_pwd, helper);
        free(curr_pwd);
    }
    free(old_pwd);
    return (g_exit_status);
}





