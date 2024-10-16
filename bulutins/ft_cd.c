/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/16 10:09:05 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int cd_errors(void)
{
    g_helper.exit_status = 1;
    write(2, M_SHELL, 23);
    write(2, "cd : too many arguments\n", 25);
    return (g_helper.exit_status);
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
    set_var(&oldpwd_node, &helper->envp,&helper->xenv);
    set_var(&currpwd_node, &helper->envp,&helper->xenv);
    free(old_pwd);
    free(curr_pwd);
}


int change_directory(char *go_path)
{
    struct stat path_stat;
    
    if (!stat(go_path, &path_stat) && !S_ISDIR(path_stat.st_mode))
    {
        handle_cd_error(go_path, 3);
        g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    if (!S_ISDIR(path_stat.st_mode))
    {
        handle_cd_error(go_path, 1);
        g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    if (chdir(go_path) != 0)
    {
        handle_cd_error(go_path, 2);
        g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    return (g_helper.exit_status);
}


int ft_cd(t_list *list, t_helper *helper)
{
    char *old_pwd;
    char *curr_pwd;
    char *go_path;
    char *home_path;
    if (!list) {
        g_helper.exit_status = 1;
        return 1;
    }

    if (count_arg(list) != 1 && count_arg(list) != 0)
        return cd_errors();

    if (count_arg(list) == 0)
    {
        home_path = ft_getenv(helper->envp,"HOME");
        if (!home_path)
            return (cd_home_not_set());
        go_path = strdup(home_path);
    } 
    else
    {
        go_path = get_target_path(list, helper);
        if (!go_path)
            return (g_helper.exit_status = 1, 1);
    }

    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        free(go_path);
        return (g_helper.exit_status = 1, 1);
    }

    if (change_directory(go_path) == 0)
    {
        curr_pwd = getcwd(NULL, 0);
        if (curr_pwd)
        {
            update_pwd(old_pwd, curr_pwd, helper);
            free(curr_pwd);
        }
    }

    free(old_pwd);
    free(go_path);
    return (g_helper.exit_status = 0, 0);
}

