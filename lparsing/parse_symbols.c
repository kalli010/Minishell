/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:49:22 by zelkalai          #+#    #+#             */
/*   Updated: 2024/10/19 23:49:23 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	validate_tokens(char *str, int *i, int *s)
{
	if (str[0] == '<')
	{
		if (str[0 + 1] != '<')
			*s = *s + 2;
		else
		{
			*s = *s + 2;
			*i = *i + 1;
		}
	}
	else if (str[0] == '&')
	{
		if (str[0 + 1] == '&')
		{
			*s = *s + 2;
			*i = *i + 1;
		}
	}
	else if (str[0] == 40 || str[0] == 41)
		*s = *s + 2;
}

void	parse_symbols(char *str, int *i, int *s)
{
	if (str[0] == '|')
	{
		if (str[0 + 1] != '|')
			*s = *s + 2;
		else
		{
			*s = *s + 2;
			*i = *i + 1;
		}
	}
	else if (str[0] == '>')
	{
		if (str[0 + 1] != '>')
			*s = *s + 2;
		else
		{
			*s = *s + 2;
			*i = *i + 1;
		}
	}
	else
		validate_tokens(str, i, s);
}

int	validate_tokens_2(char *str, int *i)
{
	if (str[0] == '<')
	{
		if (str[0 + 1] != '<')
			return (1);
		else
		{
			*i = *i + 1;
			return (0);
		}
	}
	else if (str[0] == '&')
	{
		if (str[0 + 1] == '&')
		{
			*i = *i + 1;
			return (0);
		}
	}
	else if (str[0] == 40 || str[0] == 41)
		return (1);
	return (-1);
}

int	parse_symbols_2(char *str, int *i)
{
	if (str[0] == '|')
	{
		if (str[0 + 1] != '|')
			return (1);
		else
		{
			*i = *i + 1;
			return (0);
		}
	}
	else if (str[0] == '>')
	{
		if (str[0 + 1] != '>')
			return (1);
		else
		{
			*i = *i + 1;
			return (0);
		}
	}
	else
		return (validate_tokens_2(str, i));
}
