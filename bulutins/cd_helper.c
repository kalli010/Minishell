/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 02:07:29 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/01 06:12:12 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_directory(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
        return (EXIT_SUCCESS);
    return (S_ISDIR(path_stat.st_mode)); 
}

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
    write(2, path, strlen(path));

    if (error_type == 1)
    {
        write(2, path,ft_strlen(path));
        write(2, ": No such file or directory\n", 29);
    }
    else if (error_type == 2)
    {
        write(2, path,ft_strlen(path));
        write(2, ": Permission denied\n", 20);
    }
}
