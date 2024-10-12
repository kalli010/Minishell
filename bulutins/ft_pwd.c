/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/12 21:41:45 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_helper *helper)
{
	char *path;

	g_helper.exit_status = 0;
	path = getcwd(NULL, 0);
	if (!path) 
	{
		path = ft_getenv(helper->envp, "PWD");
		if (!path)
		{
			
			write(2, "could not get cwd\n", 19);
			return (g_helper.exit_status);
		}
		printf("%s\n", path);
		free(path);
	}
	printf("%s\n", path);
	free(path);
	return (g_helper.exit_status);
}

