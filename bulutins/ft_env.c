/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:05:05 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/15 17:52:03 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_env(t_list *list, char **env)
{
    int i;

    i = 0;
    if (count_arg(list) > 0)
    {
        write(2, M_SHELL, 23);
        write(1, "enter env with no options\n", 27);
		g_helper.exit_status = 1;
        return (g_helper.exit_status);
    }
    while (env[i])
    {
        if (ft_strchr(env[i], '='))
        {
            ft_putstr_fd(env[i], STDOUT_FILENO);
            ft_putchar_fd('\n', STDOUT_FILENO);            
        }
        i++;
    }
    return (g_helper.exit_status = 0,0);
}

