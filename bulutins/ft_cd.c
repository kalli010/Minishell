/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 17:51:43 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int cd_not_dir(void)
// {
//     g_helper.exit_status = 1;
//     write(2, M_SHELL, 23);
//     write(2, "cd: Not a directory\n", 21);
//     return (g_helper.exit_status);
// }

// static int cd_errors(int flag)
// {
//     g_helper.exit_status = 1;
//     write(2, M_SHELL, 23);
//     if (flag == 1)
//     {
//         write(2, "cd: too many arguments\n", 24); 
//         return (g_helper.exit_status);
//     }
//     if (flag == 2)
//     {
//         write(2, "cd: HOME not set\n", 18);
//         return (g_helper.exit_status);
//     }
//     if (flag == 3)
//     {
//         write(2, "cd: Not a directory\n", 21);
//         return (g_helper.exit_status);
//     }
//     if (flag == 4)
//     {
//         write(2, "cd: Permission denied\n", 23);
//         return (g_helper.exit_status);
//     }
//     return (EXIT_SUCCESS);
// }

// int change_directory(t_helper *helper, char *path)
// {
//     struct stat path_stat;
//     char pwd[MAX_PATH];
//     (void)helper;
//     if (!path)
//         return (EXIT_FAILURE);

//     if (access(path, F_OK) == -1)
//         return (cd_errors(3));
//     if (stat(path, &path_stat) == -1 || !S_ISDIR(path_stat.st_mode))
//         return (cd_not_dir());
//     if (access(path, X_OK) == -1)
//         return (cd_errors(4));
//     if (chdir(path) == -1)
//     {
//         perror("minishell: cd");
//         return (g_helper.exit_status);
//     }
//     getcwd(pwd, MAX_PATH);
//     return (EXIT_SUCCESS);  
// }

// int ft_cd(t_list *list, t_helper *helper)
// {
//     char *path;

//     if (list)
//         list = list->next; 
//     if (!list || count_arg(list) == 0)
//     {
//         path =ft_getenv(helper->envp, "HOME");
//         if (!path)
//             return (cd_errors(2));
//         return (change_directory(helper, path));
//     }
    
//     if (count_arg(list) > 1)
//         return (cd_errors(1));
//     path = list->content;
//     return (change_directory(helper, path));
// }

static int cd_errors(void)
{
    g_helper.exit_status = 1;
    write(2, "minishell : cd : too many arguments\n", 37);
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
        free(go_path);
        g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    if (!S_ISDIR(path_stat.st_mode))
    {
        handle_cd_error(go_path, 1);
        free(go_path);
        g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    if (chdir(go_path) != 0)
    {
        handle_cd_error(go_path, 2);
        free(go_path);
        g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    free(go_path);
    return (g_helper.exit_status);
}


int ft_cd(t_list *list, t_helper *helper)
{
    char *old_pwd;
    char *curr_pwd;
    
    if (!list)
        return (g_helper.exit_status = 1,1);
    if (count_arg(list) != 1 && count_arg(list) != 0)
        return cd_errors();
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
        return (g_helper.exit_status = 1,1);
    char *go_path = get_target_path(list, helper);
    if (!go_path)
        return (free(old_pwd),g_helper.exit_status = 1,1);
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
    return (g_helper.exit_status = 0,0);
}
