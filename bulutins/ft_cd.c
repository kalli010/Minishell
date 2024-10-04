/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/04 03:00:07 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int cd_not_dir(void)
{
    g_exit_status = 1;
    write(2, "minishell: cd: Not a directory\n", 32);
    return (g_exit_status);
}

static int cd_errors(int flag)
{
    g_exit_status = 1;
    if (flag == 1)
    {
        write(2, "minishell: cd: too many arguments\n", 35); 
        return (g_exit_status);
    }
    if (flag == 2)
    {
        write(2, "minishell: cd: HOME not set\n", 28);
        return (g_exit_status);
    }
    if (flag == 3)
    {
        write(2, "minishell: cd: Not a directory\n", 32);
        return (g_exit_status);
    }
    if (flag == 4)
    {
        write(2, "minishell: cd: Permission denied\n", 33);
        return (g_exit_status);
    }
    return (EXIT_SUCCESS);
}

int change_directory(t_helper *helper, char *path)
{
    struct stat path_stat;
    char pwd[MAX_PATH];
    (void)helper;
    if (!path)
        return (EXIT_FAILURE);

    if (access(path, F_OK) == -1)
        return (cd_errors(3));
    if (stat(path, &path_stat) == -1 || !S_ISDIR(path_stat.st_mode))
        return (cd_not_dir());
    if (access(path, X_OK) == -1)
        return (cd_errors(4));
    if (chdir(path) == -1)
    {
        perror("minishell: cd");
        return (g_exit_status);
    }
    getcwd(pwd, MAX_PATH);
    return (EXIT_SUCCESS);  
}

int ft_cd(t_list *list, t_helper *helper)
{
    char *path;

    if (list)
        list = list->next; 
    if (!list)
    {
        path = ft_getenv(helper->envp, "HOME");
        if (!path)
            return (cd_errors(2));
        return (change_directory(helper, path));
    }
    if (count_arg(list) > 1)
        return (cd_errors(1));
    path = list->content;
    return (change_directory(helper, path));
}




