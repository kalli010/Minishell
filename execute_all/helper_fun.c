/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 06:16:39 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/09/02 07:01:53 by ayel-mou         ###   ########.fr       */
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
void my_free(t_helper *helper)
{
	free(helper->cmd);
	free_array(helper->option);
	free(helper);
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
