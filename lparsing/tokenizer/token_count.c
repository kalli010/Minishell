/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:23 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:24 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo_check(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			j = i;
			while (str[++i] != ' ' && str[i] != '\0')
				;
			if (!ft_strncmp(&str[j], "echo", i - j))
				return (1);
			if (str[i] == '\0')
				i--;
		}
	}
	return (0);
}

void	parse_symbols_and_words(char *str, int *i)
{
	char	q;

	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' || str[*i] == '&'
		|| str[*i] == 40 || str[*i] == 41)
	{
		while (str[*i] != '\0' && str[*i] != ' ')
			(*i)++;
	}
	else
	{
		while (str[*i] != '\0' && str[*i] != '|' && str[*i] != '<'
			&& str[*i] != '>' && str[*i] != '&' && str[*i] != ' '
			&& str[*i] != 40 && str[*i] != 41)
		{
			if (str[*i] == 34 || str[*i] == 39)
			{
				q = str[*i];
				while (str[++(*i)] != q)
					;
			}
			(*i)++;
		}
	}
}

int	echo_token_count(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			c++;
			if (c == 1)
			{
				while (str[i] != '\0' && str[i] != ' ')
					i++;
			}
			else
				parse_symbols_and_words(str, &i);
			if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&'
				|| str[i] == 40 || str[i] == 41)
				i--;
			if (str[i] == '\0')
				i--;
		}
	}
	return (c);
}

void	parse_token_with_quotes(char *str, int *s, int *i)
{
	char	q;

	*s = *i;
	while (str[*i] != '\0' && (str[*i] != ' ' && (str[*i] < 9 || str[*i] > 13)))
	{
		if (str[*i] == 34 || str[*i] == 39)
		{
			q = str[*i];
			while (str[++(*i)] != q)
				;
		}
		(*i)++;
	}
}

int	token_count(char *str)
{
	int	i;
	int	c;
	int	s;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
		{
			parse_token_with_quotes(str, &s, &i);
			if (!ft_strncmp(&str[s], "echo", 4))
			{
				c += echo_token_count(&str[s]);
				return (c);
			}
			if (str[i] == '\0')
				i--;
			c++;
		}
	}
	return (c);
}
