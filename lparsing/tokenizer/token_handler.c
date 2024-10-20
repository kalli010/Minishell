/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:48:32 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:48:32 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == 40 || c == 41);
}

void	handle_special_symbol(char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] != ' ' && (str[*i] < 9 || str[*i] > 13))
		(*i)++;
}

void	handle_normal_token(char *str, int *i)
{
	char	q;

	while (str[*i] != '\0' && str[*i] != ' ' && (str[*i] < 9 || str[*i] > 13))
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

void	handle_complex_token(char *str, int *i)
{
	char	q;

	while (str[*i] != '\0' && !is_special_symbol(str[*i]) && str[*i] != ' '
		&& (str[*i] < 9 || str[*i] > 13))
	{
		if (str[*i] == 34 || str[*i] == 39)
		{
			q = str[*i];
			while (str[++(*i)] != q)
				;
		}
		(*i)++;
	}
	while (str[--(*i)] == ' ' && (str[*i] < 9 || str[*i] > 13))
		;
	(*i)++;
}

void	handle_post_symbol_token(char *str, int *i, int *x)
{
	if (is_special_symbol(str[*i]))
	{
		*x = -1;
		handle_special_symbol(str, i);
	}
	else if (str[*i] == '-' && str[*i + 1] == 'n')
	{
		while (str[++(*i)] == 'n' || str[*i] == '"' || str[*i] == '\'')
			;
		if (str[*i] != ' ')
			handle_complex_token(str, i);
	}
	else
		handle_complex_token(str, i);
	(*x)++;
}
