/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:42:50 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/25 00:56:42 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_only_bs(t_tree *root)
{
    char *str;
    int i;

    str = root->content->content;
    i = 0;
    while (str[i])
    {
        if (str[i] != '\\')
            return (0);
        i++;
    }
    printf("minishell : %s:: command not found\n", str);
    return (1); 
}

int is_only_slashes(t_tree *root)
{
    char *str;
    int i;

    str = root->content->content;
    i = 0;
    while (str[i])
    {
        if (str[i] != '/')  
            return (0); 
        i++;
    }
    return (1); 
}


int helper_check_cmd(char *cmd, char *s)
{
    struct stat dir;

    if (stat(cmd, &dir) != 0)
    {
        exit_path(s, ERROR_C);
        return (ERROR_C);
    }
    if (S_ISDIR(dir.st_mode))
    {
        write(2, cmd, strlen(cmd));
        write(2, ": Is a directory\n", 17);
        return (P_DNIED);
    }
    return (EXIT_FAILURE);
}

int check_cmd(char *cmd, char *s, char **arg)
{
    int status;

    status = helper_check_cmd(cmd, s);
    if (status != EXIT_FAILURE)
    {
        free(cmd);
        free_array(arg);
        return status;
    }
    if (access(cmd, F_OK) == -1)
    {
        exit_path(s, ERROR_C);
        free(cmd);
        free_array(arg);
        return (ERROR_C);
    }
    if (access(cmd, X_OK) == -1)
    {
        exit_path(s, P_DNIED);
        free(cmd);
        free_array(arg);
        return (P_DNIED);
    }
    return (EXIT_FAILURE);
}
