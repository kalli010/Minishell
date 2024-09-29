/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 06:16:39 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/29 06:30:19 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void my_free(t_helper *helper)
{
    if (helper)
    {
        free(helper->cmd);
        helper->cmd = NULL;
        free_array(helper->option);
        helper->option = NULL;
        free(helper);
    }
}

int	check_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_arg(t_list *list)
{
	t_list	*temp_list;
	int		count;

	count = 0;
	temp_list = list;
	temp_list = temp_list->next;
	while (temp_list && temp_list->type == OPTIONS)
	{
		count++;
		temp_list = temp_list->next;
	}
	return (count);
}
