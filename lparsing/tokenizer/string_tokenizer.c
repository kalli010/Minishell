/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:19 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:20 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_quoted_section(int *c, char *str, int *i, int *in_word)
{
	char	q;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		q = str[*i];
		while (str[++(*i)] != q)
			;
	}
	if (str[*i] == ' ')
		*in_word = 0;
	else if (str[*i] != ' ' && *in_word == 0)
	{
		(*c)++;
		*in_word = 1;
	}
}

int	count_words(char *str)
{
	int	i;
	int	c;
	int	in_word;

	i = -1;
	c = 0;
	in_word = 0;
	if (str == NULL)
		return (0);
	while (str[++i])
		skip_quoted_section(&c, str, &i, &in_word);
	return (c);
}

int	malloc_str(t_split_tokens *st, char *tokens)
{
	int	i;

	st->wd = count_words(tokens);
	i = -1;
	st->len = 0;
	while (tokens[++i])
	{
		if (tokens[i] == '"' || tokens[i] == '\'')
		{
			st->q = tokens[i];
			st->len++;
			while (tokens[++i] != st->q)
				st->len++;
		}
		if (tokens[i] != ' ')
			st->len++;
	}
	st->str = (char *)malloc(sizeof(char) * (st->len + (st->wd - 1) + 1));
	if (st->str == NULL)
		return (1);
	return (0);
}

void	skip_extra_spaces(t_split_tokens *st, char *tokens, int *i)
{
	if (tokens[*i] == ' ')
	{
		st->wd = 0;
		st->str[++st->len] = ' ';
		while (tokens[++(*i)] == ' ')
			;
	}
	if (tokens[*i] != ' ' && st->wd == 0)
	{
		st->wd = 1;
		while (tokens[*i] != '\0' && tokens[*i] != ' ')
		{
			if (tokens[*i] == '"' || tokens[*i] == '\'')
			{
				st->q = tokens[*i];
				st->str[++st->len] = tokens[*i];
				while (tokens[++(*i)] != st->q)
					st->str[++st->len] = tokens[*i];
			}
			st->str[++st->len] = tokens[(*i)++];
		}
		(*i)--;
	}
}

int	split_tokens(char *tokens, char **tkn)
{
	int				i;
	t_split_tokens	st;

	if (malloc_str(&st, tokens))
		return (1);
	i = -1;
	st.len = -1;
	st.wd = 0;
	while (tokens[++i])
	{
		if (tokens[i] == '"' || tokens[i] == '\'')
		{
			st.q = tokens[i];
			st.str[++st.len] = tokens[i];
			while (tokens[++i] != st.q)
				st.str[++st.len] = tokens[i];
			st.str[++st.len] = tokens[i++];
		}
		skip_extra_spaces(&st, tokens, &i);
	}
	st.str[++st.len] = '\0';
	free(tokens);
	*tkn = st.str;
	return (0);
}
