/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:17:36 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/21 01:27:18 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	addred_front(t_redirect **lst, t_redirect *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

int	open_fd(char *file, int type)
{
	int	fd;
	int	duped_fd;

	fd = open_files(file, type);
	if (fd == -1)
		return (-1);
	if (type == INPUT)
		duped_fd = STDIN_FILENO;
	else
		duped_fd = STDOUT_FILENO;
	return (duplicate_fd(fd, duped_fd, file));
}
