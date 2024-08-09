/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:44:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/09 06:54:33 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**get_envp(char **env)
{
    int i;
    
    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH=", 5))
        i++;
    if (env[i] == NULL)
        return NULL;
    return (ft_split(env[i] + 5, ':'));
}

char    *get_path(t_helper *helper, t_list *list)
{
    char *path;
    char **dir;
	char *temp;
    int i;

    i = 0;
    dir = get_envp(helper->envp);
    if (dir == NULL)
        return (NULL);
    if (list->type == PATH_COMMAND)
    { 
        if (access(list->content, F_OK) == 0)
        {
            free_array(dir);
            return(ft_strdup(list->content));
        }

    }
    if  (list->type == COMMAND)
    {
        while (dir[i] != NULL)
        {
            temp = ft_strjoin(dir[i], "/");
            path = ft_strjoin(temp, list->content);
            free(temp);
            if (access(path, F_OK) == 0)
            {
                free_array(dir);
                return (path);
            }
            free(path);
            i++;
        }
    }
   
    free_array(dir);
    return (NULL);
}

char **get_options(t_helper *helper, t_list *list)
{
    int i;
    int count;
    char **op;
    t_list *temp_list;
    temp_list = list;
    count = 0;
    if (get_path(helper, list) ==  NULL)
        return (NULL);
    temp_list = temp_list->next;
    while (temp_list && temp_list->type == OPTIONS)
    {
        count++;
        temp_list = temp_list->next;
    }
    op = (char **)malloc((count + 2) * sizeof(char *));
    if (!op)
        return NULL;
    op[0] = get_path(helper, list);
    if (!op[0])
    {
        free(op);
        return NULL;
    }
    list = list->next;
    i = 1;
    while (list && list->type == OPTIONS)
    {
        op[i] = ft_strdup(list->content);
        list = list->next;
        i++;
    }
    op[i] = NULL;
    return op;
}
