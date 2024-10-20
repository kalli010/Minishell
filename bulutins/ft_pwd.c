/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/20 15:59:20 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_helper *helper)
{
	char *path;
	char	buff[4096];
	g_helper.exit_status = 0;
	
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		printf("%s\n", buff);
		return (g_helper.exit_status);
	}
	else 
	{
		path = ft_getenv(helper->envp, "PWD", -1);
		if (!path)
		{
			write(2, "could not get cwd\n", 19);
			return (g_helper.exit_status);
		}
	}
	printf("%s\n",path );
	free(path);
	return (g_helper.exit_status);
}


