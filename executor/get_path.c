/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:44:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/16 16:47:01 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char **get_envp(char **env)
{
    char *path;
    char **split_path;

    if (env == NULL)
        return (NULL);
    path = ft_getenv(env, "PATH", -1);
    if (path == NULL)
        return (NULL);
    path = check_path(path);
    split_path = ft_split(path, ':');
    free(path);
    return split_path;
}

char *find_in_path(char **dir, char *cmd)
{
    char *path;
    char *temp;
    int i = 0;

    while (dir[i] != NULL)
    {
        temp = ft_strjoin(dir[i], "/");
        if (!temp)
            return NULL;
        path = ft_strjoin(temp, cmd);
        free(temp);
        if (!path)
            return NULL;
        if (access(path, F_OK) == 0)
            return path;
        free(path);
        i++;
    }
    return NULL;
}

char *get_cmd_path(t_helper *helper, t_list *list)
{
    char **dir;
    char *path;

    dir = get_envp(helper->envp);
    if (dir == NULL)
        return NULL;
    path = find_in_path(dir, list->content);
    free_array(dir);
    if (path)
        return path;
    return NULL;
}

char *get_path_of_cpath(t_list *list)
{
    if (access(list->content, F_OK ) == 0)
        return ft_strdup(list->content);
    g_helper.flag = 1;
    return NULL;
}

char *get_path(t_helper *helper, t_list *list)
{
    char *path = NULL;
    g_helper.flag = 0;
    if (list->type == COMMAND)
        path = get_cmd_path(helper, list);
    else if (list->type == PATH_COMMAND)
        path = get_path_of_cpath(list);
    return path;
}
