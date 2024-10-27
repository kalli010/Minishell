/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_quotes_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:47:12 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:47:15 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_words(int *i, int *end, char *str)
{
	char	q;

	while (str[*i] && str[*i] == ' ')
		(*i)++;
	*end = *i;
	while (str[*end] && str[*end] != ' ')
	{
		if (str[*end] == '"' || str[*end] == '\'')
		{
			q = str[*end];
			while (str[++(*end)] != q)
				;
		}
		(*end)++;
	}
}

int	count_quotes(char *str)
{
	int		i;
	char	q;
	int		q_n;

	q_n = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			q_n++;
			q = str[i];
			while (str[++i])
			{
				if (str[i] == q)
					break ;
			}
			if (str[i] == '\0')
				i--;
		}
	}
	return (q_n);
}

int	check_qts(char **str, int *j, int *q_n, char q)
{
	if ((*str)[*j] == '"' || (*str)[*j] == '\'')
	{
		q = (*str)[*j];
		(*str)[*j] = (*str)[*j + 1];
		while ((*str)[*j + 1])
		{
			if ((*str)[*j + 1] == q)
				break ;
			(*str)[*j] = (*str)[*j + 1];
			(*j)++;
		}
		(*j)++;
		if ((*str)[*j] == '\0')
			return ((*str)[*j - 1] = '\0', 1);
		while ((*str)[++(*j)])
			(*str)[*j - 2] = (*str)[*j];
		(*str)[*j - 2] = '\0';
		(*q_n)--;
		*j = -1;
	}
	return (0);
}

void	remove_quotes_string(char *str)
{
	int		j;
	int		q_n;
	char	q;

	q = '\0';
	j = -1;
	if (str == NULL)
		return ;
	q_n = count_quotes(str);
	while (str[++j] && q_n != 0)
	{
		if (check_qts(&str, &j, &q_n, q))
			return ;
	}
}

int	set_words(char **str, t_var_split *vs, char **list)
{
	if ((*str)[*vs->i] == '\0')
		return (1);
	list[(*vs->c)++] = ft_substr(*str, *vs->i, *vs->end - *vs->i);
	if (list[*vs->c - 1] == NULL)
	{
		*vs->i = -1;
		while (++(*vs->i) < *vs->c - 1)
			free(list[*vs->i]);
		free(list);
		return (2);
	}
	*vs->i = *vs->end;
	return (0);
}
