/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 04:57:51 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 04:47:17 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_list(t_list *list)
{
	t_list *tmp;
	
	while (list != NULL)
	{
		tmp  = list;
		list =  list->next;
		if (tmp->content != NULL)
			free(tmp->content);
		free(tmp);
	}
}

static int	ft_all_isdigit(char *data)
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

static int	exit_erros(int status)
{
	if (status == 1)
	{
		write(2, "minishell : exit: too many arguments\n", 38);
		return (EXIT_FAILURE);
	}
	else
	{
		write(2, "minishell : exit numeric argument required", 43);
		exit(EXIT_FAILURE);
	}
}

unsigned char	ft_exit(t_tree *root, t_helper *helper)
{
	unsigned char status;

	status =  helper->exit_status;
	printf("exit\n");
	if (count_arg(root->content) > 1)
		return (exit_erros(1));
	if (root->content->next && root->content->next->content
		&& !ft_all_isdigit(root->content->next->content))
		return (exit_erros(0));
	else
	{
		if (root->content->type == OPTIONS)
			status = ft_atoi(root->content->next->content);
		free_list(root->content);
		my_free(helper);
		
	}
	exit(status);
}
