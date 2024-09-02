/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 04:57:51 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 03:15:55 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_all_isdigit(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!ft_isdigit(data[i]))
			return (0);
		i++;
	}
	return (1);
}
int  exit_erros(int status)
{
	
	if (status == 1)
	{
		write(2,"minishell : exit: too many arguments\n",38);
		return (EXIT_FAILURE);
	}
	else
	{
		write(2,"minishell : exit numeric argument required",43);
		exit(EXIT_FAILURE);
	}
}

int  ft_exit(t_tree *root,t_helper *helper)
{
	
	printf("exit\n");
	if (count_arg(root->content) > 1)
		return (exit_erros(1));
	if (root->content->next && root->content->next->content && !ft_all_isdigit(root->content->next->content))
		return (exit_erros(0));
	if (root->content->type == OPTIONS)
		helper->exit_status = ft_atoi(root->content->next->content);
	
	exit(helper->exit_status);
}