/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:25:21 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/04 03:26:05 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_exec_access(char *filename)
{
    if (filename[0] == '.' || filename[0] == '/')
    {
        if (access(filename, X_OK) != 0)
        {
			g_exit_status = 126;
			write(2,"minishell: ",12);
			write(2, filename, ft_strlen(filename));
			write(2, " : Permission denied\n", 22);
            return (g_exit_status);
        }
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
