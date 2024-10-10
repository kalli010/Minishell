/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 06:16:39 by ayel-mou          #+#    #+#             */
/*   Updated: 2024/10/10 16:56:25 by ayel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	my_free(t_helper *helper)
{
	if (helper)
	{
		if (helper->cmd)
		{
			free(helper->cmd);
			helper->cmd = NULL;
		}
		if (helper->option)
		{
		    free_array(helper->option);
		    helper->option = NULL;
		}
		free(helper);
		helper = NULL;
	}
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
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
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

void free_redirect_list(t_redirect **redlst)
{
    t_redirect *current;
    t_redirect *next;

    if (!redlst || !(*redlst))
        return;
    
    current = *redlst;
    while (current)
    {
        next = current->next;
        free(current->filename);
        free(current); 
        current = next;
    }
    *redlst = NULL;
}

void free_tree(t_tree *root)
{
  int i;
  t_tree *child;

  i = -1;
  if(root == NULL)
  {
    free(root->content->content);
    free(root->content);
    free(root);
    return;
  }
  child = root->first_child;
  while(child)
  {
    free_tree(child);
    child = child->next_sibling;
  }
}