/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:44:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/20 20:19:57 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char **get_envp(char **env)
{
    char *path;
    char **split_path;

<<<<<<< HEAD
    // if (env == NULL)
    //     return (NULL);
    if (env ==  NULL)
    {
        path = ft_strdup(DEFAULT_PATH);
        path = check_path(path);
        printf(" path is %s",path);
        split_path = ft_split(path, ':');
        free(path);
        return split_path;
    }
    path = ft_getenv(env, "PATH");
=======
    if (env == NULL)
        return (NULL);
    path = ft_getenv(env, "PATH", -1);
>>>>>>> 7b9fec5a359f20b6b4a63ec393a37c572557bed5
    if (path == NULL)
        return (NULL);
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
