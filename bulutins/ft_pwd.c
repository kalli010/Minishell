/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 06:06:57 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/08/30 06:54:37 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_list *list)
{
	char	buff[4096];

	if (list->next->type == OPTIONS)
	{
		write(1,"please enter pwd without arguments\n",36);
		return(EXIT_FAILURE);
	}
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		printf("%s \n", buff);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
