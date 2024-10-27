/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:51:32 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 13:27:14 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_str(t_split_symbols *ss, char *str)
{
	int	i;
	int	s;

	s = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			ss->q = str[i];
			while (str[++i] != ss->q)
				;
		}
		parse_symbols(&str[i], &i, &s);
	}
	ss->tmp = (char *)malloc(sizeof(char) * (i + s + 1));
	if (ss->tmp == NULL)
		return (1);
	return (0);
}

void	insert_symbol_with_spaces(
	t_split_symbols *ss, char *str, int *i, int *s)
{
	ss->check = parse_symbols_2(&str[*i], i);
	if (ss->check == 1)
	{
		ss->tmp[(*s)++] = ' ';
		ss->tmp[(*s)++] = str[*i];
		ss->tmp[(*s)++] = ' ';
	}
	else if (ss->check == 0)
	{
		ss->tmp[(*s)++] = ' ';
		ss->tmp[(*s)++] = str[*i];
		ss->tmp[(*s)++] = str[*i];
		ss->tmp[(*s)++] = ' ';
	}
	else
		ss->tmp[(*s)++] = str[*i];
}

int	split_symbols(char *str, char **cmd)
{
	int				i;
	int				s;
	t_split_symbols	ss;

	if (update_str(&ss, str))
		return (1);
	i = -1;
	s = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			ss.q = str[i];
			ss.tmp[s++] = str[i];
			while (str[++i] != ss.q)
				ss.tmp[s++] = str[i];
			ss.tmp[s++] = str[i];
		}
		else
			insert_symbol_with_spaces(&ss, str, &i, &s);
	}
	ss.tmp[s] = '\0';
	*cmd = ss.tmp;
	return (0);
}
