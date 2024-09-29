/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/29 08:51:00 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_list *list)
{
	char	buff[4096];

	g_exit_status = 1;
	if (count_arg(list) > 0)
	{
		write(1, "please enter pwd  with no options\n", 35);
        return (g_exit_status);
	}
	
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		printf("%s\n", buff);
		return (EXIT_SUCCESS);
	}
	perror("minishell : pwd");
    return (g_exit_status);
}
