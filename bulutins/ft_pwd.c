/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/11 15:32:12 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_list *list,t_helper *helper)
{
	char *path;
	g_exit_status = 0;
	(void)helper;
	if (count_arg(list) > 0)
	{
		g_exit_status = 1;
		write(2, M_SHELL, 23);
		write(2, "please enter pwd  with no options\n", 35);
        return (g_exit_status);
	}
	if (!getcwd(NULL,0))
	{
		path = ft_getenv(helper->envp,"PWD");
		if (!path)
		{
			write(2,"could not get cwd\n", 19);
			return (g_exit_status = 1, 1);	
		}
		printf("%s\n",path);
		free(path);
		return (g_exit_status);
		
	}
	path = getcwd(NULL,0);
	printf("%s\n",path);
	return (g_exit_status);
}
