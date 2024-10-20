/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulutins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:33:33 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 20:54:04 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_target_path(t_list *list, t_helper *helper)
{
    char *go_path;
    
    go_path = NULL;
    if (list)
        list = list->next;
    if (!list || !list->content)
    {
        go_path =ft_getenv(helper->envp, "HOME", -1);
        if (!go_path)
        {
            write(2, M_SHELL, 23);
            write(2, "cd: HOME not set\n", 18);
            return (NULL);
        }
    }
    else if (list->type == OPTIONS)
    {
        go_path = ft_strdup(list->content);
        if (!go_path)
            return (NULL);
    }        
    return (go_path);
}


void handle_cd_error(const char *path, int error_type)
{
    write(2, M_SHELL, 23);
    write(2,"cd",2);
    if (error_type == 1)
    {
        write(2, path,ft_strlen(path));
        write(2, ":  no such file or directory\n", 30);
    }
    else if (error_type == 3)
    {
        write(2, path,ft_strlen(path));
        write(2, ":  Not a directory\n", 20);
    }
    else if (error_type == 2)
    {
        write(2, path,ft_strlen(path));
        write(2, ": Permission denied\n", 20);
    }
}
int cd_home_not_set(void)
{
    write(2, M_SHELL, 23);
    write(2, "cd: HOME not set\n", 18);
    g_helper.exit_status = 1;
    return (g_helper.exit_status);
}
