/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:52:13 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/28 02:00:43 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_wildcard(t_list *node)
{
	int	i;

	i = -1;
	while (node->content[++i])
	{
		if (node->content[i] == '*')
			return (1);
	}
	return (0);
}

void	skip_wildcards(t_list **list, t_list **tmp, int d)
{
	if (d != 0)
	{
		clean_wildcards(list);
		*tmp = *list;
		while (*list && d > 0)
		{
			*list = (*list)->next;
			d--;
		}
	}
}

void	process_wildcard_for_entry(t_list **list, t_list **tmp, DIR *dir)
{
	struct dirent	*entry;
	int				d;

	while (*list)
	{
		if (has_wildcard(*list))
		{
			*tmp = (*list)->back;
			d = 0;
			rewinddir(dir);
			entry = readdir(dir);
			while (entry != NULL)
			{
				if (!implementing_wildcards((*list)->content, entry->d_name))
				{
					wildcards_linked_list(*list, entry->d_name);
					d++;
				}
				entry = readdir(dir);
			}
			skip_wildcards(list, tmp, d);
		}
		if (*list)
			*list = (*list)->next;
	}
}

void	reset_linked_list(t_list **list, t_list *tmp)
{
	if (tmp == NULL)
		return ;
	*list = tmp;
	while ((*list)->back)
		*list = (*list)->back;
}

int	wildcards(t_list **list)
{
	DIR		*dir;
	t_list	*tmp;

	tmp = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (1);
	process_wildcard_for_entry(list, &tmp, dir);
	reset_linked_list(list, tmp);
	closedir(dir);
	return (0);
}
