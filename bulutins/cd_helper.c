/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 02:07:29 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/03 01:36:42 by ayel-mou         ###   ########.fr       */
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
        go_path = ft_getenv(helper->envp, "HOME");
        if (!go_path)
        {
            write(2, "minishell: cd: HOME not set\n", 28);
            return (NULL);
        }
    }
    else if (list->type == OPTIONS)
    {
        go_path = ft_strdup(list->content);
        if (!go_path)
            return (NULL);
    }        
    return go_path;
}


void handle_cd_error(const char *path, int error_type)
{
    write(2, "minishell: cd: ", 15);
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
