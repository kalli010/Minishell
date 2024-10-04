/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/03 08:03:27 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_list *list,t_helper *helper)
{
	
	if (count_arg(list) > 0)
	{
		g_exit_status = 1;
		write(2,"minishell ", 11);
		write(2, "please enter pwd  with no options\n", 35);
        return (g_exit_status);
	}
	printf("%s\n",helper->pwd);
	return (g_exit_status);
}
