/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:13 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/25 12:45:42 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process_token(int *i, int s, t_tokenizer *tk)
{
	(*tk->tokens)[*tk->j] = ft_substr(tk->str, s, *i - s);
	if ((*tk->tokens)[*tk->j] == NULL)
	{
		free_all_tokens(*tk->tokens, *tk->j);
		return (1);
	}
	(*tk->j)++;
	return (0);
}

int	handle_echo_token(int s, t_tokenizer *tk)
{
	if (!ft_strncmp(&tk->str[s], "echo", 4) || !ft_strncmp(&tk->str[s],
			"\"echo\"", 6))
	{
		if (echo_create_tokens(&tk->str[s], tk))
			return (1);
		return (0);
	}
	return (-1);
}

void	skip_non_whitespace(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != ' ' && (str[*i] < 9 || str[*i] > 13))
	{
		if (str[*i] == 34 || str[*i] == 39)
			skip_quoted_part(str, i);
		else
			(*i)++;
	}
}

int	create_tokens_loop(t_tokenizer *tk)
{
	int	i;
	int	j;
	int	s;
	int	ec;

	i = -1;
	j = 0;
	tk->j = &j;
	while (tk->str[++i])
	{
		if (tk->str[i] != ' ' && (tk->str[i] < 9 || tk->str[i] > 13))
		{
			s = i;
			skip_non_whitespace(tk->str, &i);
			ec = handle_echo_token(s, tk);
			if (ec == 1 || ec == 0)
				return (ec);
			if (process_token(&i, s, tk) != 0)
				return (1);
			if (tk->str[i] == '\0')
				i--;
		}
	}
	(*tk->tokens)[j] = NULL;
	return (0);
}
