/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heck_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:49:06 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:49:08 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_wildcards(t_list *list)
{
	int		i;
	char	q;

	while (list)
	{
		i = -1;
		while (list->content && list->content[++i])
		{
			if (list->content[i] == '"' || list->content[i] == '\'')
			{
				q = list->content[i];
				while (list->content[++i] != q)
					;
			}
			if (list->content[i] == '*')
				return (1);
		}
		list = list->next;
	}
	return (0);
}

int	find_exact_match(const char *filename, char *str)
{
	int	i;

	i = 0;
	while (str[i] == filename[i])
		i++;
	if (str[i] == '\0')
		return (i);
	else
		return (-1);
}

int	find_partial_match(const char *filename, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (filename[i] && filename[i] != str[j])
		i++;
	while (str[j] && filename[i] && filename[i] == str[j])
	{
		i++;
		j++;
	}
	if (str[j] == '\0')
		return (i);
	else
		return (-1);
}

int	find_full_match(const char *filename, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (filename[i] && filename[i] != str[j])
		i++;
	while (filename[i] && str[j] && filename[i] == str[j])
	{
		i++;
		j++;
	}
	if (str[j] == '\0' && filename[i] == '\0')
		return (i);
	else
		return (-1);
}

int	ft_find(const char *filename, char *str, int flag)
{
	if (flag == 0)
		return (find_exact_match(filename, str));
	else if (flag == 1)
		return (find_partial_match(filename, str));
	else
		return (find_full_match(filename, str));
}
