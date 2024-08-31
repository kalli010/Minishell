/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:46:23 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/31 02:29:59 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>




int ft_cd(t_list *list)
{
	char	*file;
	// DIR		*dir;
    // struct	dirent *entry;
	if (list->next == NULL)
	{
		if (chdir("~") == -1)
			printf("error");
		printf("%s\n",getcwd(NULL,0));
		return (EXIT_SUCCESS);
	}
	file =  list->next->content;
	printf("file is ->> %s \n ",file);
	chdir(file);
	return (EXIT_SUCCESS);
}