/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/25 02:10:20 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static int cd_errors(void)
{
    g_exit_status = 1;
    write(2, "minishell : cd : too many arguments\n", 37);
    return (g_exit_status);
}

// static void update_pwd(char *old, char *curr, t_helper *helper)
// {
//     char *old_pwd;
//     char *curr_pwd;

//     old_pwd = ft_strjoin("OLDPWD=", old);
//     curr_pwd = ft_strjoin("PWD=", curr);
//     ft_setenv(helper->envp, old_pwd);
//     ft_setenv(helper->envp, curr_pwd);
//     free(old_pwd);
//     free(curr_pwd);
// }


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
    
    if (!list)
    {
        g_exit_status = 1;
        return (g_exit_status);
    }
    if (count_arg(list) != 1 && count_arg(list) != 0)
        return cd_errors();

    char *go_path = get_target_path(list, helper);
    if (!go_path)
    {
        g_exit_status = 1;
        return (g_exit_status);
    }

    return (change_directory(go_path));
}




