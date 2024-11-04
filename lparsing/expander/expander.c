/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:50:38 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/04 23:12:50 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expander(char **env, t_list **list, int d)
{
	int	i;
	int	status;

	i = d;
	while (--d >= 0)
	{
		if ((*list)->content[d] == '"')
		{
			while (--d >= 0 && (*list)->content[d] != '"')
				;
			if (d < 0)
			{
				status = var_dquotes(env, list, i);
				return (status);
			}
		}
	}
	status = var_quotes(env, list, i);
	return (status);
}

int	check_d(char *str, int i)
{
	if (str[0] == '\0')
		return (i);
	while (str[++i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] != '$')
			return (i);
	}
	return (i);
}

int	check_squotes(char *str, int i)
{
	int		k;
	char	q;

	k = 0;
	q = '\0';
	while (k <= i)
	{
		if (str[k] == '\'' || str[k] == '"')
		{
			q = str[k];
			while (str[++k] != q)
				;
		}
		k++;
	}
	if (q == '"' || q == '\0')
		return (1);
	else
		return (0);
}

int	process_expansion(char **env, t_list **list, int i, int status)
{
	while ((*list)->content[i])
	{
		if (check_squotes((*list)->content, i))
		{
			status = expander(env, list, i);
			if (status == 1)
			{
				if ((*list)->back != NULL)
					(*list)->back->i = 2;
				break ;
			}
			else if (status == 2)
				return (1);
			if (*list)
				i = check_d((*list)->content, i - 1);
			else
				break ;
		}
		else
			i = check_d((*list)->content, i);
		if (i == -1)
			break ;
	}
	return (0);
}

int	check_expander(char **env, t_list **list)
{
	t_list	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	while (*list)
	{
		i = check_d((*list)->content, -1);
		if ((*list)->back == NULL || (*list)->back->type != HEREDOC)
			if (process_expansion(env, list, i, 0))
				return (1);
		tmp = *list;
		if (*list != NULL)
			(*list) = (*list)->next;
	}
	*list = tmp;
	if (*list != NULL)
		while ((*list)->back != NULL)
			*list = (*list)->back;
	return (0);
}
