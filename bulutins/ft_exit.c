/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 04:57:51 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/04 03:59:36 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int ft_all_isdigit(char *data)
{
    int i = 0;
    if (data[i] == '-')
        i++;
    while (data[i])
    {
        if (!ft_isdigit(data[i]))
            return (0);
        i++;
    }
    return (1);
}

static int exit_errors(int status)
{
    if (status == 1)
    {
        write(2, "minishell: exit: too many arguments\n", 37);
    }
    else if (status == 2)
    {
        write(2, "minishell: exit: numeric argument required\n", 44);
    }
    return (EXIT_FAILURE);
}

unsigned char ft_exit(t_tree *root, t_helper *helper)
{
    unsigned char status;
    char *arg;

	status = g_exit_status;
    printf("exit\n");
    if (root->content->next)
    {
        if (count_arg(root->content) > 1)
            return exit_errors(1);
        arg = root->content->next->content;
        if (!ft_all_isdigit(arg))
            return (exit_errors(2));
        status = (unsigned char)ft_atoi(arg);
        if (status < 0)
            status = 0;
    }
    free_list(root->content);
    my_free(helper);
    exit(status);
}
