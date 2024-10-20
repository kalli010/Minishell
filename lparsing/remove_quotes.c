/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:27 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 20:51:29 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_cleanup_loop(t_list *list, int *j, int *q_n)
{
	char	q;

	q = list->content[*j];
	list->content[*j] = list->content[*j + 1];
	while (list->content[*j + 1] != q)
	{
		list->content[*j] = list->content[*j + 1];
		(*j)++;
	}
	(*j)++;
	while (list->content[++(*j)])
		list->content[*j - 2] = list->content[*j];
	list->content[*j - 2] = '\0';
	(*q_n)--;
	*j = -1;
}

void	remove_quotes(t_list *list)
{
	int	j;
	int	q_n;

	if (list == NULL)
		return ;
	while (list)
	{
		q_n = count_quotes(list->content);
		j = -1;
		while (list->content[++j] && q_n != 0)
		{
			if (list->content[j] == '"' || list->content[j] == '\'')
			{
				quote_cleanup_loop(list, &j, &q_n);
			}
		}
		list = list->next;
	}
}
