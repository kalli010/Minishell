/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:25:21 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/06 03:20:47 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_permission(char *file)
{
    if (access(file, X_OK) != 0) 
    {
        g_exit_status = 126;
        write(2, "minishell: ", 12);
        write(2, file, ft_strlen(file));
        write(2, " : Permission denied\n", 22);
        return (g_exit_status);
    }
    return (g_exit_status);
}


int command_not_found(char *cmd)
{
    write(2, "minishell: ", 12);
    write(2, cmd, ft_strlen(cmd));
    write(2, ": command not found\n", 20);
    g_exit_status = 127;
    return (g_exit_status);
}

int is_dir(char *dir)
{
    g_exit_status = 126;
    write(2, "minishell: ", 12);
    write(2, dir, ft_strlen(dir));
    write(2, ": Is a directory\n", 18);
    return (g_exit_status);
}
