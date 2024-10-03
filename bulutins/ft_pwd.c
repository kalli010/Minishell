/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/03 00:36:22 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_list *list)
{
	char	buff[MAX_PATH];
	
	if (count_arg(list) > 0)
	{
		g_exit_status = 1;
		write(2,"minishell ", 11);
		write(2, "please enter pwd  with no options\n", 35);
        return (g_exit_status);
	}
	if (!getcwd(buff, MAX_PATH))
	{
		g_exit_status = 1;
		write(2,"minishell ",11);
		write(2,": pwd: Could not get cwd\n",26);
		return (g_exit_status);
	}
	write(1, buff, strlen(buff));
	write(1, "\n", 1);
	return (g_exit_status);
}
