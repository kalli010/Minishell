/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_finalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:27 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:28 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	finalize_token(int start, int end, t_tokenizer *tk, char *str)
{
	(*tk->tokens)[*tk->j] = ft_substr(str, start, end - start);
	if ((*tk->tokens)[*tk->j] == NULL)
	{
		free_all_tokens(*tk->tokens, *tk->j);
		return (1);
	}
	if (split_tokens((*tk->tokens)[*tk->j], &(*tk->tokens)[*tk->j]))
	{
		free_all_tokens(*tk->tokens, *tk->j);
		return (1);
	}
	(*tk->j)++;
	return (0);
}

void	free_all_tokens(char **tokens, int j)
{
	int	i;

	i = -1;
	while (++i < j)
		free(tokens[i]);
}

int	process_token_2(int *i, int *x, t_tokenizer *tk, char *str)
{
	int	s;

	s = *i;
	if (is_special_symbol(str[*i]))
	{
		*x = -1;
		handle_special_symbol(str, i);
	}
	else
	{
		if (*x == 0)
			handle_normal_token(str, i);
		else
			handle_post_symbol_token(str, i, x);
	}
	if (finalize_token(s, *i, tk, str) != 0)
		return (1);
	(*x)++;
	if (is_special_symbol(str[*i]))
		(*i)--;
	if (str[*i] == '\0')
		(*i)--;
	return (0);
}

int	echo_create_tokens(char *str, t_tokenizer *tk)
{
	int	i;
	int	x;
	int	result;

	i = -1;
	x = 0;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			result = process_token_2(&i, &x, tk, str);
			if (result != 0)
				return (result);
		}
	}
	(*tk->tokens)[*tk->j] = NULL;
	return (0);
}

void	skip_quoted_part(char *str, int *i)
{
	char	q;

	q = str[*i];
	while (str[++(*i)] != q)
		;
	(*i)++;
}
